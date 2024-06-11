Deadlock Handling <br/>

deadlock 처리 두 가지 방법 <br/>

Deadlock prevention <br/>
-
   1. 시스템에 '절대' deadlock에 들어가지 않도록 보장 <br/>
   2. pre-declaration - 각 트랜잭션이 실행 시작 전에 모든 데이터 lock을 요구 <br/>
   3. Graph based Protocol <br/>
      1. 데이터에 순서를 부여하고 순서에 맞게 데이터를 lock <br/>
      2. 2PL을 약간 수정하여 유사하게 사용 가능 <br/>
         1. 트랜잭션이 특정 item을 잠그면, 그 항목보다 앞선 항목에 대해 lock 요청 불가 <br/>
  4. wait-die scheme - 비선점 방식 <br/>
       1. 오래된 T가 젊은 T이 Data item을 release할 때까지 기다림 <br/>
       2. 젊은 T는 오래된 T를 절대 기다리지 X. 대신에 rollback <br/>
       3. ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/f2067c50-e355-4ca5-b7e7-3a9d24fedd8c) <br/>
  5. wound-wait scheme - 선점 방식 <br/>
       1. 오래된 T가 젊은 T에 상처를 내서 강제로 rollback시킴 <br/>
       2. 젊은 T는 오래된 T를 waiting <br/>
  6. Timeout-Based Schemes <br/>
       1. T가 lock을 '일정 시간 동안만' 기다림 <br/>
          1. 기다리고 난 이후에는, T는 timeout 후 rollback <br/>
       2. Deadlock <br/>
          1. 일부 T가 deadlock에 빠진 후, 타임아웃되어 rollback 됨 -> 해결 <br/>
       3. 구현 쉽고 ,T가 짧고, deadlock 때문에 긴 waiting의 경우 -> timeout-based schemes <br/>
       4. timeout interval을 정확하게 설정 어려움 <br/>
          1. deadlock 상태 아닌데도, 불필요하게 rollback 할 수 있음 <br/>
          2. deadlock 발생하면, 너무 오래 기다릴 수 있음 <br/>
       5. starvation 발생 가능 <br/>

Deadlock Detection  <br/>
-
Wait-for graph<br/>
노드 - T<br/>
Edge Ti -> Tj = Ti는 Tj가 unlock하는 것을 기다림<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b5cf9abb-19df-4308-b720-7dfae1e3bb47)<br/>
cycle이 있을 때만, deadlock 발생 -> 사이클이 포함된 그래프의 경우 deadlock 발생<br/>

prevention , detection두 방법 모두 트랜잭션 롤백 발생 가능<br/>

Deadlock Recovery<br/>
-
Deadlock detect 되면<br/>
1. Transaction rollback<br/>
   1. Deadlock 사이클을 깨기 위해 일부 트랜잭션을 rollback<br/>
   2. rollback할 트랜잭션을 선택할 때 비용이 최소화되는 트랜잭션을 희생<br/>
2. rollback의 범위 결정<br/>
   1. 전체 rollback - 트랜잭션을 중지하고 다시 시작<br/>
   2. 부분 rollback - 사이클의 다른 트랜잭션이 기다리고 있는 경우 해제하기위해 필요한 부분만 rollback(일부 작업만 롤백)<br/>
3. Starvation 방지<br/>
   1. 같은 트랜잭션이 희생할 경우 기아<br/>
   2. rollback 횟수를 비용에 포함시켜 해결 가능<br/>

Multiple Granularity<br/>
-
트랜잭션이 대부분의 튜플에 접근하려는 경우, 각 튜플을 lock -> 시간 소모가 크고, 메모리도 많이 차지함<br/>
-> 전체 relation을 lock할 수 있도록 허용<br/>
Granularity of locking<br/>
1. fine granularity -> 높은 동시성, 높은 lock 오버헤드<br/>
2. coarse granularity -> 낮은 동시성, 낮은 lock 오버헤드<br/>

Multiple granularity of locking 은 필요함<br/>
data item의 다양한 크기 허용<br/>
data granularity 계층 구조 정의<br/>
1. 작은 세분화는 더 큰 세분화 내에 중첩<br/>
2. 데이터 세분화 계층 구조는 tree구조로 가능(Tree protocol이랑 헷갈리지마라)<br/>

Granularity Hierarchy<br/>
-
Data item의 granularity 계층 구조 트리<br/>
Database<br/>
Area<br/>
File<br/>
Record<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ee10b1a6-6156-40ce-be1c-9865f963e11e)<br/>

T가 Tree의 노드를 명시적으로 잠그면, 해당 모드로 하위 노드를 암묵적으로 잠금<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/132d45cc-6951-499b-b7ed-97da5692bce6)<br/>

T가 레코드를 잠그려면, 해당 레코드가 lock 걸려 있는지 아닌지 확인 필요<br/>
-> 이를 위해 T는 root에서 그 레코드로 트리를 탐색하면서 서로 호환되지 않는 모드로 잠겨있는지 확인(서로 호환되지 않는 모드면 record를 잠글 수 없음)<br/>

Intention Lock Modes<br/>
S,X 말고도 3가지 모드 더 있음<br/>
intention - shared (IS) - 트리의 lower level에서 명시적으로 S-lock 할 의도가 있다고 나타냄<br/>
intention - exclusive(IX) - 트리의 lower level에서 명시적으로 S-lock or X-lock을 할 의도가 있다고 나타냄<br/>
shared and intention - exclusive (SIX) - 명시적 S-lock으로 잠그고 , lower level에서 명시적 X-lock 할 의도가 있음을 나타냄<br/>
왜 쓰나요? -> 상위 수준의 노드를 S or X모드로 잠글 때 하위 수준의 모든 노드를 확인할 필요 없이 잠글 수 있도 함<br/>

호환성 matrix<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/114872c9-2778-462f-b1ae-0422df9659e7)<br/>

Mupltiple Granularity locking scheme<br/>
-
Ti가 노드 Q를 lock할 방법<br/>
1. lock compatibility matrix를 준수<br/>
2. tree root가 먼저 잠겨야함. 모든 모드로 lock 가능<br/>
3. Ti가 Q의 부모를 IX or IS 모드로 잠근 경우에만 Q를 S or IS 모드로 잠글 수 있음<br/>
4. Ti가 Q의 부모를 IX or SIX 모드로 잠근 경우에만 Q를 X or SIX or IX 모드로 잠글 수 있음<br/>
5. Ti가 이전에 unlock 안한 경우에만 lock 가능 -> Ti는 2PL<br/>
6. Ti의 자식이 unlock일 경우에만 Q를 unlock 가능<br/>

Lock은 Root->leaf 순서로 걸지만, unlock은 leaf->root 순서로 해제<br/>
Lock granularity escalation - 특정 레벨에서 너무 많은 lock이 발생한 경우, 더 높은 granularity의 S or X lock 전환<br/>
-> 처음 말했던, 거의 모든 튜플에 lock을 걸려면 그냥 relation 전체에 lock을 걸어라.<br/>


