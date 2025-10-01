Rollout and Versioning
Deployment가 업데이트되면 rollout이 trigger되서 새로운 revision이 생김
revision은 각 배포 버전에 대해 k8s가 자동으로 부여하는 번호

kubectl rollout <subcommand> <리소스 종류>/<이름> 방식으로 사용
kubectl rollout status deployment/myapp-deployment

Deployment 2 Strategy
1. 업데이트를 하면 기존의 instance들을 지우고 새로운 버전으로 instance들을 생성하는 방식
=> 시스템 다운이 발생하는 방식으로, default 방식이 아님

2. instace 한개씩 지우고 다시 생성하는 방식
=> default 방식으로, rolling update 방식

업데이트는 apply or set image 방식으로 진행하면 됨
set image는 빠르게 cli에서 테스트 및 패치하는 용도로 사용되기 때문에, yaml과 상태가 다를 수 있어 주의해야 함

rollout undo 명령어를 통해 rollback 또한 가능함
