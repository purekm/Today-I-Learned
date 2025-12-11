
---

# Kubernetes Monitoring, Logging, Update, Command 개념 정리

## Monitoring

### Metrics 수집 및 분석 툴

* **Heapster**, **Metrics Server**, **DataDog** 등 외부 툴을 통해 k8s 리소스의 사용량을 모니터링하고 분석 가능
* **Metrics Server**

  * 클러스터 당 **1개**만 존재
  * 데이터를 **In-memory** 방식으로 저장 (디스크 저장 X)
  * **kubectl top** 명령어를 통해 리소스 사용량 확인 가능

### kubelet과 CAdvisor

* 각 **Node**에는 **kubelet**이 존재하며, 이는 **Container Advisor(CAdvisor)** 를 포함
* **CAdvisor**는 컨테이너의 **CPU, Memory, Network 등 리소스 사용량**을 수집
* Metrics Server는 이러한 정보를 모아 **k8s 전체 리소스 사용량**을 제공

---

## Logging

### Event Simulator

* **Docker의 event-simulator 이미지**를 이용해 이벤트 생성 가능
* Kubernetes에서도 동일한 이미지를 사용하여 로그를 테스트할 수 있음

### 로그 확인 명령어

```bash
kubectl logs -f event-simulator-pod
```

* 여러 컨테이너가 있는 경우, **container 이름**까지 지정해야 함:

```bash
kubectl logs -f event-simulator-pod event-simulator
```

* `-f` 옵션: **follow**의 약자로, 로그가 추가될 때마다 **실시간으로 출력**

---

## Rolling Update & Rollback

### Deployment의 업데이트 전략

1. **Recreate**

   * 기존 Pod들을 모두 **삭제 후 새로 생성**
   * 일시적으로 서비스 **중단 발생**
2. **RollingUpdate** *(기본값)*

   * Pod를 **하나씩 교체**하며 서비스 **무중단 업데이트**

### 명령어 예시

* **Strategy type 확인**

  ```bash
  kubectl describe deployment <deployment-name>
  ```
* **정의 파일 수정 후 적용**

  ```bash
  kubectl apply -f deployment.yaml
  ```
* **롤백**

  ```bash
  kubectl rollout undo deployment <deployment-name>
  ```
이때 rollout는 pod update 관련한 명령어

---

## Command & Arguments

### Dockerfile vs Kubernetes Yaml

| 구분    | Dockerfile   | Kubernetes YAML | 대응 관계                    |
| ----- | ------------ | --------------- | ------------------------ |
| 실행 명령 | `ENTRYPOINT` | `command`       | `ENTRYPOINT` ↔ `command` |
| 인자    | `CMD`        | `args`          | `CMD` ↔ `args`           |

### 우선순위

* Kubernetes의 `command` / `args`가 **Dockerfile의 설정보다 우선**

---
