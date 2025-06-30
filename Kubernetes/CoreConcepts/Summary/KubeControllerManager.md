# 🧭 Kube Controller Manager

Kube Controller Manager는 Kubernetes의 다양한 **컨트롤러(controller)** 들을 실행하고 관리하는 컴포넌트입니다.  
컨트롤러는 클러스터의 상태를 감시(watch)하고, 원하는 상태(desired state)로 유지하기 위한 조치를 취합니다.

---

## 🛠 컨트롤러의 기본 동작

1. **Watch Status**  
   현재 클러스터 상태를 지속적으로 감시

2. **Remediate Situation**  
   실제 상태가 원하는 상태와 다를 경우 자동으로 수정 작업 수행

---

## 🧩 Node Controller

노드 상태를 감시하고, 이상 상황이 발생하면 조치를 취합니다.  
Kube API Server와 통신하여 상태를 확인하고, 애플리케이션이 계속 실행되도록 유지합니다.

- **Node Monitor Period**:  
  `5초`마다 각 노드의 heartbeat 상태 확인

- **Node Monitor Grace Period**:  
  `40초` 동안 heartbeat가 없으면 해당 노드를 unreachable 상태로 간주

- **Pod Eviction Timeout**:  
  `5분` 내에 노드가 응답하지 않으면 해당 노드에 있던 Pod를 제거하고  
  다른 노드에 재할당하여 복제

---

## 🔁 복제 Controller (Replica Controller)

- Pod가 죽으면 자동으로 새로운 Pod를 생성하여 개수를 유지

---

## 🔍 Kube Controller Manager 확인 방법

- `kube-controller-manager.service`  
  → systemd 서비스로 커스텀 가능

- `kube-controller-manager-master`  
  → Master 노드에서 컨트롤러가 실행되지 않는 경우 확인

