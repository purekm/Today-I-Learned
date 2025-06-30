# 🧱 Pod와 Container 기본 개념

---

## 📦 Pod란?

- Kubernetes에서 **컨테이너는 Pod라는 캡슐로 포장**되어 실행됨
- Pod는 애플리케이션의 **단일 인스턴스**이며, Kubernetes의 **가장 작은 배포 단위**
- 클러스터 구성 구조:  
  `Cluster > Node > Pod`

---

## 📈 스케일링 전략

- 사용량 증가 시:
  - **Node에 여유가 있다면**, 동일 Node에 Pod를 추가
  - **Node 자원이 부족하다면**, Cluster에 **새로운 Node를 추가**한 뒤 Pod를 생성하여 분산 처리

---

## 🔁 Pod와 Container의 관계

- 일반적으로 **Pod 1개에 Container 1개 (1:1 구조)**
- 하지만 **Multi-Container Pod**도 존재함:
  - 보조 역할의 **Helper Container**(예: 로그 수집기, 데이터 동기화 등)를 함께 포함

---

## 📄 Kubernetes YAML의 주요 필드

Kubernetes는 리소스를 정의할 때 **YAML 파일**을 사용하며, 주요 필드는 다음과 같음:

- `apiVersion`: 리소스가 사용하는 API 버전 (문자열)
- `kind`: 리소스의 종류 (예: Pod, Service 등, 문자열)
- `metadata`: 리소스 이름, 네임스페이스 등의 메타 정보 (딕셔너리 형식)
- `spec`: 리소스의 구체적인 동작 정의 (리스트 또는 배열 형식)

---

## 🔍 Pod 상태 확인 명령어

- 현재 클러스터에 존재하는 Pod 목록 확인:
  ```bash
  kubectl get pods
  kubectl describe pod myapp-pod