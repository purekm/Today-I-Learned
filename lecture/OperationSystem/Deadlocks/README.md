8장 Dead Lock <br/> 미 검토 상태
Deadlock의 특성 및 필요조건<br/>
Mutual exclusion  - 적어도 하나의 자원이 공유 불가 때문에 deadlock<br/>
Hold and wait – 뭔가를 잡고 대기중 <br/>
No preemption – Task가 끝나야 자원을 놓는데, 자원을 안 놓으면 deadlock<br/>
Circular wait – 원형 대기가 있음<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/0ef22853-3b60-44cb-82d0-46adf274dfcf)
deadlock 발생 <br/>

Single instance 일 경우에는 cycle이면 deadlock, deadlock 이면 cycle이다. 필요충분조건 <br/>
Multiple instances 일 경우에는 deadlock 이면 cycle이다. <br/>

Deadlock Handling<br/>
Deadlock을 예방하고 회피하고 탐색하는 등 cost가 비싸기 때문에 대부분의 OS가 무시한다. (미사일 이런건 데드락 걸리면 안되니까 deadlock 방지를 해줌)<br/>

Deadlock Prevention<br/>

Mutual Exclusion<br/>
-
상호 배제를 전부 막아 버리기엔 무리<br/>

Hold and wait 을 remove<br/>
-
시작하기 전에 필요하나 자원을 다 가져 감<br/>
잡고 있는 자원이 없을 때만 자원을 요청<br/>

No preemption<br/>
-
자원 할당이 불가능하면 가지고 있는 자원을 다 내놓게 함<br/>
대기 중인 프로세스의 자원을 반납하게 함<br/>
자원을 다 할당 받을 수 있을 때 까지 프로세스를 시작하지 않음.<br/>

3가지 방법 모두 구현하기 어려움<br/>

Circular Wait<br/>
-
가장 현실적인 방법으로, 자원을 획득할 때 일련 번호를 붙여서 순차적으로 함<br/>
1. 1번 자원을 얻었으면 2번 자원을 얻는 방식<br/>
2. 어떤 자원을 요청할 때 그 자원보다 높은 순서의 자원을 가질 수 없다.<br/>

Deadlock Avoidance<br/>
현재 상태를 파악함<br/>

Safe State<br/>
현재 창고에 있는 자원을 써서 작업이 진행했을 때, 순차적으로 성공하면 safe state<br/>
시스템에 있는 모든 프로세스가 각자 필요한 자원을 사용할 수 있는 실행 순서가 존재할 때 우리는 시스템이 safe state<br/>

시스템이 safe state - > no deadlock<br/>
시스템이 unsafe state - > deadlock 가능성 존<br/>
1. Avoidance는 항상 시스템이 안전한 상태를 유지하도록 안전하게 유지할 수 있을 때만 자원을 할당함<br/>
안전한 상태인지 알아야함<br/>

Single instance of resource type 일 경우에는 resource-allocation graph로 판단<br/>
1. Cycle이 발생하지 않을 때만 request를 들어 줌<br/>

Multiple instance of resource type일 경우에는 Banker’s Algorithm 로 판단<br/>
1. 각 프로세스는 사용할 자원의 최대치를 사전에 선언해야 함<br/>
2. 프로세스가 원하는 모든 자원을 확보하면 작업을 마친 후에 모두 반납<br/>

MAX = 최대로 필요한 것. 2차원배열인 이유는 프로세스가 여러 개고, resource type도 여러 개이기 때문에. Max[i,j] =k라면 i가 j를 하려면 최대 k개의 instance가 필요<br/>

Available – 창고안에 m 종류의 resource가 있는데, 각 resource의 개수<br/>

Allocation – 어떤 프로세스에 어떤 resource를 할당할 것 인지<br/>

Need – 현재 allocation 된 개수가 있지만, 작업을 마치려면 더 필요한 개수 <br/>

Safety Algorithm<br/>
현재 상태가 안전한지 검증<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/3d9050f7-5499-481e-9011-a7a5b22df485)

실패했을 때를 대비해서 복사본인 work 생성<br/>
Deadlock Detection - Single instance 인 경우<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6d48079b-1a76-462c-ae72-01b77aebf181)


Several instances 인 경우<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/2055d2dd-3bec-4faf-88ad-7b2b1918388f)

Dead lock 발생 가능 <br/>
request만큼 못 주면 걔네들 때문에 deadlock 발생<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/642c2189-d678-4947-8869-79140a44a9c0)

P1,P2,P3,P4 때문에 deadlock 발생<br/>

Deadlock 을 recovery를 하기 위해서는 deadlock에 걸린 프로세스들을 abort한다.<br/>
모든 deadlock에 걸린 프로세스를 죽이거나, 하나씩 죽여보는 방식이 있다.<br/>
하나씩 죽일 때 어떤 순서로 abort 해야 해?<br/>
 ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/75f098a1-297d-4b13-9140-a6e8617c0c57)

