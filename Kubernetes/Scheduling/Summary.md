# Kubernetes 스케줄링 및 Admission Controller 핵심 정리

---

## 1. 스케줄링 (Scheduling) 기법

### 1.1 Manual Scheduling (수동 스케줄링)
* 스케줄러를 거치지 않고 수동으로 파드를 배치하는 방법
* Pod 설정 파일에 `nodeName` 필드를 직접 작성하여 특정 노드에 강제로 할당

### 1.2 Label and Selector
* **Service ↔ Pod 연결의 핵심 메커니즘**
* Service는 `selector`를 통해 Pod에 부착된 `label`을 검색하여 트래픽을 전달할 타겟 Pod를 찾음

### 1.3 NodeSelector
* 가장 기본적인 노드 선택 방법
* Pod가 특정 `label`을 가진 노드에만 스케줄링되도록 단순 매칭

### 1.4 NodeAffinity (노드 어피니티)
* `nodeSelector`의 상위 호환 기능으로, 필수/선호 조건 및 복잡한 논리 표현식(Operator) 지원
* **스케줄링 조건:**
    * `requiredDuringScheduling...`: 조건에 맞아야만 스케줄링 **(필수)**
    * `preferredDuringScheduling...`: 가능하면 조건에 맞춰서 스케줄링 **(선호/권장)**
* **Operator (표현식):**
    * `Exists`: Key의 존재 여부만 확인 (Value 설정 불필요)
    * `In`: Key의 값이 Value 목록 중 하나와 일치하면 스케줄링 허용
    * `NotIn`: Key의 값이 Value 목록에 포함되지 않으면 스케줄링 허용 (제외 처리)

### 1.5 Taints and Tolerations (테인트와 톨러레이션)
* **Taints (테인트):** Node에 적용하는 제약 조건 (이 노드에는 파드를 배치하지 마라)
* **Tolerations (톨러레이션):** Pod에 적용하여 특정 Taint가 있는 노드에도 스케줄링될 수 있게 제약을 완화/무시하는 설정
* **Taint 형식:** `key=value:effect`
* **Effect 3종류:**
    * `NoSchedule`: 일치하는 Toleration이 없는 새 Pod의 스케줄링 금지
    * `PreferNoSchedule`: 가능하면 새 Pod 스케줄링을 피함 (Soft 제한)
    * `NoExecute`: 일치하는 Toleration이 없으면 새 Pod 스케줄링 금지는 물론, **이미 실행 중인 기존 Pod도 노드에서 쫓아냄(Evict)**

---

## 2. Resource Limits (리소스 제한)

* **requests:** Pod 스케줄링의 기준이 되는 최소 보장 리소스 (이만큼은 무조건 보장해 줌)
* **limits:** 런타임 시 Pod가 사용할 수 있는 최대 리소스 상한선
* **초과 시 동작:**
    * **CPU 초과 시:** 쓰로틀링(Throttling) 발생하여 성능 저하 유발
    * **Memory 초과 시:** OOMKilled 발생하며 Pod 강제 종료
* **권장 구성 (Requests and No limits):**
    * `requests`만 설정하고 `limits`는 설정하지 않는 방식이 이상적일 수 있음. 파드가 필요한 만큼의 기본 자원은 보장받으면서, 노드에 여유 자원이 있을 때 제한 없이 리소스를 끌어다 쓸 수 있어 효율적임.

---

## 3. Admission Controller (어드미션 컨트롤러)

API 서버로 들어온 요청이 파드로 생성되기까지의 파이프라인:
> **Authentication (인증: 사용자/인증서 확인) → Authorization (인가: RBAC 권한 확인) → `Admission Controller` → Pod 생성**

* **역할:** RBAC만으로는 제어할 수 없는 세밀한 영역을 통제하는 플러그인. 리소스 생성을 허용/거부하거나, 강제로 값을 수정 및 기본값을 채워 넣음.
* **유형 (실행 순서: Mutating → Validating):**
    1. **Mutating Controller:** 조건에 따라 요청의 내용을 수정하거나 기본값을 주입
    2. **Validating Controller:** 최종적으로 요청의 유효성을 검증하여 조건을 만족하지 않으면 요청 거부(Reject)

### 3.1 Admission Webhook
Kubernetes 내장 플러그인 외에 **사용자 자체 로직**을 적용하기 위해 웹훅 서버를 연동하는 방법

* **구성 단계:**
    1. **웹훅 서버 배포:** 커스텀 로직이 담긴 서버 배포 (클러스터 내 배포 시 Service 리소스 포함 필수)
    2. **Admission Webhook Config 작성:** 웹훅 트리거 설정 및 Client Config 정의 (어떤 API 요청이 올 때 웹훅 서버로 보낼지 설정)
* **전체 흐름:**
    * `kubelet` → `API Server` (Authentication → Authorization → **Admission Controller [Webhook 호출을 통해 자체 판단 로직 개입]**) → 파드 생성 승인 및 Create Pod 진행
