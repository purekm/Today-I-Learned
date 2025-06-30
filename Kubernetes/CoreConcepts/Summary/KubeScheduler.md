# ⚖️ Scheduler & Kubelet

Kubernetes에서 Pod가 **어느 Node에 배치될지 결정하는 컴포넌트는 Scheduler**입니다.  
그러나 실제로 Pod를 실행시키는 작업은 **Kubelet**이 담당합니다.

---

## 🚦 Scheduler의 역할

- Scheduler는 Pod가 실행될 **최적의 Node를 선택**함
- 선택만 할 뿐, 직접 Pod를 이동시키지는 않음

### 📌 스케줄링 과정

1. **Filter Nodes**  
   → CPU, 메모리 등 자원이 부족한 Node는 제외

2. **Rank Nodes**  
   → 필터를 통과한 Node 중에서 남은 자원이 많은 순으로 우선순위 지정  
   → 사용자 정의 방식의 우선순위 설정도 가능

---

## 🔧 Kubelet의 역할

- **각 Worker Node의 관리자 역할**을 수행  
- Scheduler가 선택한 Node에 실제로 Pod를 실행시킴
- Container Runtime과 통신하여 이미지 기반으로 컨테이너 생성

> 📌 Kubelet은 각 Worker Node에 **직접 설치해야 하며**,  
> `kubeadm`이 자동으로 설치해주지 않음 (수동 구성 필요)

