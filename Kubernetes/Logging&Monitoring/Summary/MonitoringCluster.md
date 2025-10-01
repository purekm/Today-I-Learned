
지표들을 모니터링하고 데이터에 대한 분석을 해주는 여러가지 tool들이 있음

k8s의 특징들을 분석해주는건 외부의 tool로 처리
heapster, Metrics Server, Data Dog 같은 tool

k8s는 각 노드에 kubelet을 놔둠
이는 Container Advisor을 포함하고 있음
CAdvisor는 컨테이너의 리소스 사용량 수집을 해줌

Logging 
Docker에서 event-simulator로 이벤트를 만들어주는 용도
k8s에서도 이 event-simulator 이미지를 사용해서 이벤트를 생성하면, log 명령어로 로그를 볼 수 있음
kubectl log -f event-simulator-pod
여기서 -f는 파일이 아니라, follow의 약자로 로그가 추가될 때마다 실시간으로 보여줌

