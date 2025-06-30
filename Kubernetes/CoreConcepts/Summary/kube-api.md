# 🚪 kube-apiserver

Kubernetes에서 kube-apiserver는 클러스터의 핵심 컴포넌트입니다.  
모든 요청은 API를 통해 전달되며, kubectl 또한 이 API를 활용합니다.

---

## 🧩 역할

- Kubernetes의 모든 리소스 객체 간 통신은 API를 통해 수행됨  
- 사용자는 kubectl을 통해 명령을 실행하며, HTTP POST 방식으로 직접 API 요청도 가능  
- kube-apiserver는 ETCD와 직접 통신하여 상태 데이터를 저장하거나 불러옴

---

## 📦 Pod 생성 흐름

1. **Authenticate User**  
   요청을 보낸 사용자의 신원을 인증

2. **Validate Request**  
   요청 형식과 권한 유효성 검사  
   → 이 단계에서 Pod 객체는 생성되지만, 아직 노드에는 할당되지 않음

3. **Retrieve Data**  
   Pod 생성 명령을 해석하고 처리

4. **Update ETCD**  
   새로운 Pod 정보가 ETCD에 저장됨

5. **Scheduler 작동**  
   스케줄러가 node가 없는 Pod를 감지  
   적절한 Worker Node를 선정하여 kube-apiserver에 알림

6. **Kubelet 작업**  
   해당 Node의 kubelet이 Container Runtime에 명령을 내려 이미지를 기반으로 Pod를 생성  
   생성 후 상태를 kube-apiserver 및 ETCD에 업데이트

---

## 🧭 핵심 요약

- 클러스터를 변경하는 모든 작업은 kube-apiserver를 통해 수행됨
- kube-apiserver는 ETCD와 직접 연결되어 클러스터 상태를 실시간 반영
- 인증 → 유효성 검증 → 저장 → 실행 → 반영의 과정을 거침
