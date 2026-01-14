````md
# OS Upgrade, Cluster Upgrade, etcd 백업/복원 정리

---

## 1. OS Upgrade (Node 유지보수)

Node의 **OS/커널 업그레이드**를 하려면 보통 **재부팅 또는 서비스 중지**가 필요하다.  
이때 해당 Node에 있던 Pod가 가능한 한 영향을 받지 않도록, `drain` / `cordon` / `uncordon`을 사용한다.

### 1.1 drain / cordon / uncordon 개념

- `kubectl drain <노드명>`  
  - 노드를 **유지보수 모드**로 전환하고,  
    그 노드에서 실행 중인 Pod를 다른 노드로 옮길 수 있게 만든다.

내부적으로 일어나는 일:

1. 노드가 **Cordon** 상태가 되어 **스케줄 불가(Unschedulable)** 처리됨.
2. 노드에 있던 일반 Pod들이 **Eviction API**를 통해 순서대로 종료됨.
3. 그 Pod들을 관리하는  
   `ReplicationController`, `ReplicaSet`, `Deployment`, `StatefulSet` 등이  
   **다른 노드에 새 Pod를 자동 생성**.
4. 모든 일반 Pod가 사라지면, 해당 Node는 **비워진 상태**가 됨.

- `kubectl cordon <노드명>`
  - 해당 노드를 **스케줄 불가** 상태로 만들어  
    **새 Pod는 더 이상 스케줄링되지 않게** 한다.
  - 이미 떠 있는 Pod는 그대로 유지되며 “퇴거(evict)” 되지 않는다.

- `kubectl uncordon <노드명>`
  - 유지보수 후 노드를 다시 **스케줄 가능 상태**로 되돌린다.

### 1.2 OS 업그레이드 절차 예시

1. 노드를 drain:
   ```bash
   kubectl drain <노드명> --ignore-daemonsets --delete-emptydir-data
````

2. OS/커널 업그레이드 및 재부팅.
3. 노드가 다시 Ready 상태가 되면:

   ```bash
   kubectl uncordon <노드명>
   ```

### 1.3 강제 drain 시 주의사항

* 노드를 **강제로 drain** 했을 때(`--force` 사용 등),

  * **ReplicaSet/Deployment에 속하지 않은 Pod**(고아 Pod)들은 **삭제**되며,
  * 다시 자동 생성되지 않을 수 있다.
* 따라서 중요한 Pod는 항상 Deployment/StatefulSet 등 **컨트롤러로 관리**하는 것이 좋다.

---

## 2. Cluster Upgrade

### 2.1 컴포넌트 버전 관계 (Version Skew)

모든 컴포넌트가 **완전히 같은 버전일 필요는 없다.**
다만 **kube-apiserver보다 더 높은 버전의 컴포넌트가 먼저 올라가면 안 된다**는 원칙이 있다.

일반적인 업그레이드 순서(논리적):

1. `kube-apiserver`
2. `kube-controller-manager` & `kube-scheduler`
3. `kubelet` & `kube-proxy`

* 상위 컴포넌트(특히 API Server)와 **같은 버전이거나, 그보다 낮은 버전**으로 맞추되
* **하위 컴포넌트를 API Server보다 더 높은 버전으로 먼저 올리는 것은 피한다.**

### 2.2 지원 버전 및 업그레이드 단계

* Kubernetes는 공식적으로 **최신 3개의 minor 버전**만 지원.
* 업그레이드는 **한 minor 버전씩** 올리는 것이 권장된다.

  * 예: `1.10 → 1.11 → 1.12`

### 2.3 클러스터별 업그레이드 방식

* **GKE/Cloud Managed Kubernetes**

  * 보통 Cloud 콘솔/CLI에서 제공하는 업그레이드 기능 사용
* **kubeadm 기반 클러스터**

  * `kubeadm upgrade` 명령어 사용

### 2.4 업그레이드 전략

1. **Master(Control Plane) Node 업그레이드**
2. Control Plane이 안정화된 후, **Worker Node 업그레이드**

Worker Node 업그레이드 전략 예:

* 모든 Worker Node를 한 번에 교체
  → 다운타임 발생 가능 (보통 권장 X)
* Worker Node를 **하나씩 순차적으로**
  `drain → 업그레이드 → uncordon`
* 아예 **새 버전 노드를 새로 생성**하고
  기존 노드를 워크로드 이동 후 폐기하는 방식

---

## 3. kubeadm으로 업그레이드할 때의 상세 흐름

### 3.1 Control Plane 업그레이드

1. **먼저 저장소 정보 및 패키지 버전 확인**

   ```bash
   sudo apt update
   sudo apt-cache madison kubeadm
   ```

2. **kubeadm 패키지 업그레이드**

   ```bash
   sudo apt-get install -y kubeadm=1.12.0-00
   ```

3. **업그레이드 계획 확인 및 실행**

   ```bash
   sudo kubeadm upgrade plan
   sudo kubeadm upgrade apply v1.12.0
   ```

> 여기까지 해도 `kubectl get nodes`에 표시되는 노드 버전은 그대로일 수 있다.
> 노드 버전은 **kubelet 버전 기준**이기 때문.

4. **kubelet 업그레이드**

   ```bash
   sudo apt-get install -y kubelet=1.12.0-00
   sudo systemctl restart kubelet
   ```

5. 이후 `kubectl get nodes`로 확인하면
   Control Plane 노드의 버전이 새 버전으로 보이게 된다.

### 3.2 Worker Node 업그레이드

각 Worker 노드에 대해 같은 패턴 수행:

1. 해당 노드를 drain:

   ```bash
   kubectl drain <worker-node> --ignore-daemonsets --delete-emptydir-data
   ```
2. 해당 노드에서:

   ```bash
   sudo apt update
   sudo apt-cache madison kubeadm
   sudo apt-get install -y kubeadm=<버전>
   sudo kubeadm upgrade node     # worker 노드용
   sudo apt-get install -y kubelet=<버전>
   sudo systemctl restart kubelet
   ```
3. 다시 스케줄 가능하게:

   ```bash
   kubectl uncordon <worker-node>
   ```

### 3.3 OS 버전 확인

* 노드 OS 버전 확인:

  ```bash
  cat /etc/*release*
  ```

---

## 4. etcd 백업과 복구

### 4.1 etcd data-dir와 스냅샷

* **data-dir**

  * etcd 데이터(클러스터 상태)가 저장되는 디렉터리
  * 일반적으로 `/var/lib/etcd`
* etcd는 **스냅샷(snapshot)** 생성 기능 제공

  * 스냅샷 파일은 보통 `.db` 확장자로 현재 디렉토리(또는 지정 디렉토리)에 생성

### 4.2 TLS 인증 옵션 의미 (etcdctl 사용 전 준비)

`etcdctl`로 접속할 때는 TLS 인증 설정이 필요하다:

* `--cacert`

  * 서버에서 보내준 인증서를 검증하기 위한 **CA 인증서**
* `--cert`

  * 클라이언트(우리가) 서버에 보낼 **클라이언트 인증서**
* `--key`

  * 위 인증서에 대응하는 **개인 키**
* `--endpoints`

  * 접속할 etcd 서버 주소 (예: `https://127.0.0.1:2379`)

### 4.3 스냅샷 생성 (온라인 백업, etcdctl)

```bash
ETCDCTL_API=3 etcdctl \
  --endpoints=https://127.0.0.1:2379 \
  --cacert=/etc/kubernetes/pki/etcd/ca.crt \
  --cert=/etc/kubernetes/pki/etcd/server.crt \
  --key=/etc/kubernetes/pki/etcd/server.key \
  snapshot save /backup/etcd-snapshot.db
```

* 실행 시점의 etcd 데이터를 `.db` 파일로 저장.
* 스냅샷 상태 조회:

  ```bash
  ETCDCTL_API=3 etcdctl snapshot status /backup/etcd-snapshot.db
  ```

### 4.4 스냅샷 복구 절차 (restore)

1. **kube-apiserver 중지**

   * static Pod 환경이면 `/etc/kubernetes/manifests/kube-apiserver.yaml`를 잠시 다른 위치로 옮겨서 정지시킬 수 있음.

2. **스냅샷 복원 (새 data-dir 사용)**

   ```bash
   ETCDCTL_API=3 etcdctl \
     --cacert=/etc/kubernetes/pki/etcd/ca.crt \
     --cert=/etc/kubernetes/pki/etcd/server.crt \
     --key=/etc/kubernetes/pki/etcd/server.key \
     snapshot restore /backup/etcd-snapshot.db \
     --data-dir=/var/lib/etcd-restored
   ```

3. **새 data-dir을 사용하도록 etcd 설정 변경**

   * `/etc/kubernetes/manifests/etcd.yaml`에서
     `--data-dir=/var/lib/etcd-restored` 로 수정

4. **systemd 재로딩 및 서비스 재시작 (필요 시)**

   ```bash
   sudo systemctl daemon-reload
   sudo systemctl restart etcd
   # 이후 kube-apiserver static manifest 되돌려 재시작
   ```

5. 클러스터 상태 확인:

   ```bash
   kubectl get nodes
   kubectl get pods -A
   ```

## 5. Lab 팁 요약
node를 drain 할때, deployment가 아니라 그냥 pod는 force drain을 하면 삭제됨


* **controlplane이 접속하는 etcd endpoint 찾기**

  * etcd Pod의 설정(예: `/etc/kubernetes/manifests/etcd.yaml`)에서
    `--listen-client-urls` / `--advertise-client-urls` 확인.

* **etcd snapshot 생성 시 기억해야 할 4가지 요소**

  1. `--endpoints`
  2. `--cacert`
  3. `--cert`
  4. `--key`

* **snapshot 복원 후 주의점**

  * `--data-dir`를 **새 디렉토리**로 지정해서 복원한 다음,
  * etcd 설정 파일(예: `etcd.yaml`)에서 data-dir 경로를 **복원된 경로**로 변경해야
    실제로 복원된 데이터가 사용된다.


