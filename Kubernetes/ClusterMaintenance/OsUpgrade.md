OS upgrade
Node의 OS나 커널을 업그레이드 하려면 Node를 재부팅하거나 중지시켜야함
=> 이때 pod가 영향받지 않기 위해서 drain/ uncordon 명령어 사용
- kubectl drain: 노드를 유지보수 모드로 전환하고, 그 노드에서 실행 중인 pod를 다른 노드로 옮기기

내부적으로 일어나는 일
노드가 Cordon 되어 스케줄 불가 처리됨.
노드에 있던 Pod들이 Eviction API 를 통해 순서대로 종료됨.
ReplicationController, ReplicaSet, Deployment가 새 Pod을 다른 노드에 자동 생성.
모든 일반 Pod이 사라지면, Node가 비워진 상태가 됨.

Lab

Drain 후 node가 비워지면 OS를 업그레이드하고,
이후에 다시 노드가 스케줄링 가능하게 하도록 uncordon 명령어 사용
cordon 명령어는 해당 노드를 스케줄링 못하게 만드는데, drain과는 다르게 방출시키지 않음

노드를 강제로 drain 했을 때, ReplicaSet에 속하지 않은 Pod들은 삭제됨


Cluster upgrade
모든 컴포넌트들이 같은 버전을 사용할 필요는 없음
=> But kube api서버 보다 더 높은 버전을 사용하는 것은 안됌
1️⃣ kube-apiserver  →  2️⃣ controller-manager & scheduler  →  3️⃣ kubelet & kube-proxy 
같아도 되지만, 하위의 컴포넌트가 더 높은 버전을 사용하면 안됌

버전은 업그레이드 시킬 수 있음
쿠버네티스는 최신 3개의 버전만을 지원함
업그레이드할때는 한 단계씩 올리는 게 좋음 (ex 1.10 -> 1.11)

클러스터마다 업그레이드하는 방식이 다름
- Google 클러스터: console 조작
- Kubeadm: kubeadm upgrade 명령어 사용

클러스터를 업그레이드하는 방식
1. Master Node 업그레이드
2. Master Node 업그레이드되는 동안 Worker Node 업그레이드
Worker Node를 업그레이드하는 여러 전략이 있음
- 모든 노드를 한번에 교체(다운타임 발생)
- 한번에 노드 1개씩 업그레이드(모든 노드를 최신 버전으로 업그레이드 할때까지 동일한 절차)
- 새로운 버전의 노드를 생성하고, 기존의 노드 폐기

kubeadm을 통해 클러스터를 업그레이드하는데, controlplane 요소 업그레이드 한 이후에는 kubelet은 수동으로 업그레이드 해야함
먼저 kubeadm 업그레이드
=> apt-get upgrade -y kubeadm=1.12.0-00
=> kubeadm upgrade apply v1.12.0

위를 통해 클러스터를 업그레이드해도, get node를 했을 때 노드들의 버전은 똑같음
=> kubelet의 버전이 나오는 것이기 때문에 이는 수동으로 업그레이드 해줘야함

apt-get upgrade -y kubelet=1.12.0-00으로 kubelet 버전 설치 후,
systemctl restart kubelets로 재실행
이후 확인해보면 master node의 버전이 upgrade된 것을 확인할 수 있음
이때부터 worker node 업그레이드 시작
1번 node를 업그레이드하면, 해당 워크로드들은 다른 노드들에게 넘겨줘야함(drain)
업그레이드 이후에는 uncordon 명령어로 unscheduling을 해제해줘야 함

Demo: Upgrading Cluster
/etc/*release* 에 사용하고 있는 버전이 나옴

Lab
Master Node Upgrade(Workder node upgrade)
1. 먼저 저장소에 패키지 다운로드
2. sudo apt update && sudo apt-cache madison kubeadm 를 통해 패키지 업데이트 및 저장소의 패키지 버전 출력
3. kubeadm upgrade plan && kubeadm apply ~
4. apt-get install 로 kubelet 설치
5. 재시작 

Master node는 apply, worker node는 upgrade node를 사용

Backing up and Restore Method
etcd의 data-dir: 모든 데이터가 저장되는 곳
etcd는 snapshot 생성도 가능(생성시 현재 디렉토리에 생성)

Restore 절차
1. kube-apiserver stop
2. etcdctl snapshot restore ~ /복원 디렉토리 를 통해 스냅샷으로 복원
3. systemctl daemon-reload && restart etcd && kube-apiserver

etcdctl을 사용하기 전에 TLS인증이 필요한데, 이를 위해 옵션들을 작성해두면 TLS 인증을 해줌
- cacert : 상대방이 인증서를 주면 ca의 공개키로 확인하기 위함 
- server.crt : 상대방에게 보낼 인증서
- server.key : 내 개인 키인데, 상대방에게 보낼 인증서에 서명하기 위함
- 엔드포인트 : 

| 구분         | etcdctl                                                | etcdutl                          |
| ---------- | ------------------------------------------------------ | -------------------------------- |
| 백업 방식      | **라이브(운영 중)** etcd에 API로 접근해 스냅샷 생성                    | **오프라인(정지 상태)** 에서 파일 시스템 복제     |
| 결과물        | `.db` 스냅샷 파일                                           | etcd data-dir 복사본                |
| etcd 실행 여부 | 실행 중이어야 함                                              | 종료 상태여야 안전함                      |
| 주요 명령      | `snapshot save`, `snapshot status`, `snapshot restore` | `backup`, `snapshot restore`     |
| 복구 방법      | `.db` 파일을 `snapshot restore`로 복구                       | 백업 디렉터리를 `/var/lib/etcd`에 그대로 복사 |
| 사용 목적      | 운영 환경 백업, 빠른 복원 가능                                     | 오프라인 백업, 디스크 레벨 복사용              |

Lab
controlplane이 연결되어있는 etcd cluster에 접근할 수 있는 주소 찾기
=> etcd pod에서 listen-client-url 찾기

etcd snapshot 생성할 때, 4가지 요소 잘 적어두기

etcd snapshot 복원할 때, --data-dir을 통해서 원래 주소가 아닌 새로운 주소로 복원하도록 작성해줌
이후 /etc/kubernetes/manifest 에서 정적파일인 etcd.yaml 수정하는데, data-dir을 내가 복원한 주소로 수정해야 복원됨
