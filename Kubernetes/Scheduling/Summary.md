Manual Scheduling
- 수동으로 스케줄링
- nodename을 직접 작성

Label and Selector
Service <-> Pod 연결의 핵심으로,
Service는 Selector로 pod의 label을 통해 맞는 pod를 찾음

Taints and Tolerations
Taints: Node에다가 조건을 거는 것
Tolerations: Pod에 Node의 조건을 완화하는 것

taint
key=value:effect 
effect 3종
- NoSchedule: 새 Pod 스케줄 금지
- PreferNoSchedule: 가능하면 새 Pod 스케줄 금지
- NoExecute: 이미 존재하는 Pod도 toleration이 없다면 쫓아냄

NodeSelector
Pod에 특정 label을 가진 노드 매칭 가능하도록 함

NodeAffinity
nodeSelector의 상위호환으로, 조건 + 필수/선호 + 표현식 가능.
=> 복잡한 표현 가능
requiredDuringScheduling: 조건에 맞아야만 스케줄링
preferredDuringScheduling: 가능하면 조건에 맞춰서 스케줄링

operator
- Exist: 존재만 확인 (값을 비교하지 않아서 value가 필요없음)
- In: key 값이 value 중 하나면 ok
- NotIN: key 값이 value에 없으면 ok

ResourceLimits
request: 스케줄링 기준
limit: 런타임 상한
CPU가 초과되면 쓰로틀링, Memory가 초과되면 OMMKilled
Request and No limits가 가장 이상적
=> 필요한 만큼만 사용하고, 한 쪽에서 많은 리소스를 필요하면 limits에 막히지않으니까 좋음

Admission Controller
요청이 API 서버에 도달하면, Authentication 프로세스(인증서 확인)를 거침
이후 Authorization 프로세스(사용자 권한 확인)를 거침
RBAC로는 확인할 수 없는 영역이 있음
=> Admission Controller 사용
리소스를 허용/거부 하거나, 자동으로 수정/기본값을 채우는 플러그인
Admission Controller는 여러 종류가 있음

Mutating Controller: 요청을 수정할 수 있음
Validating Controller: 요청을 검증하여 조건 불만족이면 거부

Mutating -> Validating 순으로 진행됨

Admission Webhook
자체 로직이 있는 웹훅 서버를 배포하고, k8s에서 웹훅 구성하는 controller단계의 한 방법

단계
1. 웹훅 서버 배포(클러스터 내에 배포할 경우 서비스 포함해서 잘 배포하기)
2. Admission Webhook Config 
2번 단계에서 웹훅 트리거 설정 및 Client Config 작성

kubelet -> API Server(Authentication -> Authorization -> Admission Controller) -> Create Pod

API Server는 인증 및 권한 확인을 하고, admission 단계에서 필요하면 웹훅을 통해서 admission controller의 판단을 적용함
