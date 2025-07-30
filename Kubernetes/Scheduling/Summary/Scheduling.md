Scheduling

Scheduling은 pod 를 node에 binding 해줌
Scheduler가 없으면 pod는 pending 상태가 됨
=> pod-bind-definition 파일에 name: node 이름을 작성하면 해당 pod가 노드에 바인딩됨

Labels & Selector

Labels
같은 특징을 가진 그룹으로 정의
리소스에 부여하는 키-값 메타데이터

Selectors
특정 label을 가진 리소스를 찾기 위한 필터 역할

Taints & Tolerations

Taint
노드에 제한 조건을 걸어 pod가 마음대로 스케줄되지 못하게 함 
=> 노드에 제한 조건을 검
kubectl taint nodes node-name key=value:taint-effect
ex) kubectl taint nodes node1 app=blue:NoSchedule

taint effect에는 NoSchedule, PreferNoSchedule, NoExecute 방식이 존재함

NoSchedule - Toleration이 없으면 절대 스케줄 안됨
PreferNoSchedule - 최대한 해당 노드에 pod가 스케줄되지않도록 노력하는 방식으로, 보장되지않음
NoExecute - 기존에 있던 Pod가 조건을 만족하지 못하면 쫓아내고, toleration을 만족하지 못하면 스케줄도 안됨

Toleration
Pod가 특정 Taint를 사용해도 괜찮게 만들어서, 스케줄이 가능하게 함
=> pod에 조건 완화를 시킴

definition file에 toleration 카테고리에 key, operator, value, effect를 작성해줘야 함
 

Node Selector
특정 Label을 가진 노드에만 스케줄되도록 함
kubectl label nodes <node-name> <label-key>=<label-value>
ex)kubectl label nodes node1 size=large

한계점으로는 And 조건만 가능하고 나머지 다른 비교 및 복잡한 조건 불가능
더 복잡한 조건을 사용하려면 Node Affinity 사용

Node Affinity
Pod가 특정 조건을 만족하는 노드에만 스케줄되도록 제어하는 기능
nodeSelector보다 복잡한 논리(In, NotIn, Exists, OR, 우선순위 등)를 표현할 수 있음

Type에 3가지가 존재

Availiable
requiredDuringSchedulingIgnoreDuringExecution : 조건에 맞는 노드가 있어야함
preferredDuringSchedulingIgnoreDuringExecution : 조건에 맞는 노드를 찾아보고, 없으면 아무 노드에 pod를 넣음
둘 다 실행중일 때 변화가 생겨도 무시함

Planned
requiredDuringSchedulingRequiredDuringExecution : 조건에 맞아야 스케줄하고, 실행중에도 계속 조건을 확인함

Taint & Toleration과 Node Affinity를 함께 사용하면 Pod를 원하는 노드에 스케줄링 할 수 있음

Resource Limits
CPU, MEM에 따라서 노드에 리소스들을 적재하는데, 만약 pod를 노드에 적재하려는데 공간이 없으면 Pending 상태가 됨

Resource 

requests section:
Pod가 node에 적재될 때 최소한 보장되어야 하는 자원량

limits section:
Pod 가 사용할 수 있는 최대 자원

만약 Limit를 초과한다면?
CPU가 초과될 경우엔 속도 제한 발생
MEM이 초과될 경우엔 컨테이너가 강제로 종료되며, OOM 에러가 함께 발생

Limit Range도 설정 가능하며,
Resoure Quotas를 사용해서도 설정 가능

Static Pod
Control Plane에 의해 관리되지 않는 Pod로, kubelet이 직접 관리
Manifest는 yaml파일 이라고 생각하면 되는데, 이들이 생성되는 장소를 설정할 수 있음
kubelet.service에 --config=kubeconfig.yaml 이라고 작성하고,
kubeconfig.yaml 
staticPodPath: /etc/~ 처럼 설정하면 staticPodPath를 설정할 수 있음

runtime 환경에 따라 다를 수 있지만, static pod를 생성하면 아래의 명령어로 확인할 수 있음
Docker : docker ps
containerd : nerdctl ps
cri-o : crictl ps

Static Pod와 Daemonset은 둘다 자동으로 Pod를 실행하는 방식
Static Pod는 Kubelet에 의해 생성되고, DaemonSet은 Kube-API Server을 통해 생성됨
Static Pod는 로컬용 Pod, DaemonSet은 중앙제어 Pod라고 생각하면 편할 것 같음

Priority Classes
Pod에 우선순위를 부여하는 정책으로, namespace가 필요하지 않음
value 값으로 우선순위를 설정함

Databasesm Critical Apps, Jobs들은 1,000,000,000 ~ -2,147,483,648 까지의 값으로 설정 가능
Kubernetes Componenets는 우선순위가 높은 만큼 system이 정한 높은 value가 존재함 1,000,000,000 ~ 2,000,000,000

priority-class.yaml 파일을 통해 priority를 설정할 수 있음
PriorityClass.yaml에 globalDefault 값을 설정하면, Pods들은 priorityClassName을 명시하지 않으면 globalDefault값이 들어감

만약 노드에 리소스가 없는데, 추가적인 작업이 들어온다면 priority-class.yaml의 preemptionPolicy에 따라 조치됨
만약 PreemptLowerPriority 라면, 추가적인 작업의 우선순위가 높다면 LowerPriority를 가진 job을 kill 하고 preempt하게 됨
Never 옵션을 사용하면 절대 다른 Pod를 쫓아내지 않음



