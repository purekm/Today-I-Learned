Serverless
- 기본 인프라를 보거나 액세스할 수 없음
- 없는 것 처럼 관리할 필요 없음

Lambda
- 트리거를 구성하면, Lambda 함수는 서비스가 트리거되기를를 기다림
- 실행시간이 보통 15분 이하인 코드만 작동되기 때문에, 딥러닝 같은 장기 실행 프로세스에는 적합하지 않음


기본 환경에 access 해야지만 효율성과 휴대성이 필요한 상황이 있을 수 있음
-> Container Service 사용

Amazon Elastic Computing Service(ECS)
Amazon Elastic Kubernetes Service(EKS)

컨테이너 오케스트레이션 도구로, 컨테이너는 Docker 컨테이너를 의미함
EC2 단일 인스턴스 뿐만 아니라 클러스터도 시작, 중지 재시작, 모니터링하는 프로세스 = 오케스트레이션
컨테이너 관리를 지원하기 위해 만든 도구들

AWS Fargate
- 기본 OS에 access할 필요가 없거나, EC2 instance를 관리할 필요가 없는 경우
- ECS 또는 EKS용 서버리스 컴퓨팅 플랫폼

정리

EC2
- 기존 애플리케이션 호스팅
- OS에 대한 전체 액세스

Lambda
- 단기 실행 함수 호스팅
- 서비스 중심 or 이벤트 기반 애플리케이션
- 서버 관리하지 않음

AWS에서 Docker 컨테이너 기반 워크로드 실행시키려면 오케스트레이션 선택
- ECS
- EKS 
이후에는 내가 컨테이너를 관리하려면 EC2 를 사용
아니면 AWS Fargate를 사용