Lock-based protocols 2<br/>

Two Phase locking protocol<br/>
-
Phase 1 - Growing Phase<br/>
1. 트랜잭션이 lock을 얻을 수 있음<br/>
2. 트랜잭션이 lock을 해제할 수 없음<br/>

Phase 2 - Shrinking Phase<br/>
1. 트랜잭션이 lock을 해제할 수 있음<br/>
2. 트랜잭션이 새로운 lock을 얻을 수 없음<br/>

Two Phase locking protocol은 conflict-serializability를 보장함<br/>
트랜잭션이 최종 lock을 얻은 시점(lock point)의 순서로 직렬화 가능<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/9c375065-facc-41ed-aaab-d6e68d58db2a)<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/910c7fae-097d-4cb9-bd7a-5ae6137143d6)<br/>
T1과 T2는 Not Two Phase Protocol<br/>
어떤 lock을 해제를 하고 새로운 lock을 얻을 수 없음<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/42896b21-71e5-4d22-a746-0965726b572e)<br/>
T3와 T4는 Two Phase Protocol<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/90b4a6b4-f79a-4abf-8d20-3c5fc7b55fd1)<br/>
deadlock으로부터 자유롭지 않음<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/544a705c-8cba-4751-9799-9820cf19bc8a)<br/>
cascading rollback으로부터 자유롭지 않음<br/>

Cascading rollback 방지를 위한 two phase locking의 확장<br/>
-
Strict two-phase locking<br/>
1. 트랜잭션이 커밋 or 중단될 때까지 모든 X-lock을 보유<br/>
   1. 회복가능성을 보장하고, cascading rollback을 방지<br/>

Rigorous two-phase locking<br/>
1. 트랜잭션이 커밋 or 중단될 때까지 모든 lock을 보유<br/>
   1. 트랜잭션을 커밋 순서로 직렬화 가능<br/>

대부분의 DB는 rigorous two-phase locking을 구현하는데, 걍 two-phase locking이라고 부름<br/>

Lock Conversion<br/>
-
트랜잭션이 실행 중에 특정 데이터 항목에 대한 lock을 변경할 경우<br/>
1. 데이터 항목을 읽기 위해 S-lock을 걸고, 데이터를 수정하기위해 X-lock으로 변경<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/775417a0-2992-42d7-b432-500eed3fb389)<br/>
<img width="367" alt="image" src="https://github.com/purekm/Today-I-Learned/assets/90774046/f4febae2-8d38-49ee-8886-e055ffbc147d"><br/>


규칙<br/>
1. X-lock으로 upgrade<br/>
   1. 트랜잭션이 Growth 단계에서만 가능<br/>
2. S-lock으로 downgrade<br/>
   1. 트랜잭션이 Shrinking 단계에서만 가능<br/>

Two-phase protocol을 사용하면서 lock conversion을 적용하면 conflict serializability를 보장<br/>

더 많은 동시성 가능해짐<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/79c7ab35-a0a0-445f-9fd3-5f3256261e32)<br/>


Locking protocol<br/>
-
스케줄 S가 locking protocol을 따르는 트랜잭션 set에 의해 생성될 수 있다면? legal<br/>
protocol이 serializability를 보장하면, 해당 프로토콜 하 모든 legal schedule은 직렬 가능<br/>
Two phase locking protocol은 serializability를 보장함. -> 2PL protocol 하의 모든 legal schedule은 직렬 가능<br/>

그렇지만 2PL protocol은 serializability를 위한 필요조건은 X<br/>
2PL을 안 쓰고도 conflict-serializability를 보장하는 스케줄 존재<br/>
추가 요구사항이 2PL이 아닌 프로토콜도 conflict-serializability를 보장할 수 있음<br/>

Automatic Acquisition of locks<br/>
-
Ti - 명시적인 lock call 없이 표준 read/write instruction을 발행<br/>
read(D) 작업의 처리<br/>

      if Ti has a lock on D
      then 
         read(D)
      else begin
         if necessary, wait until no other transaction has a lock-X on D
         grant Ti a lock-S on D;
         read(D);
      end

write(D) 작업의 처리<br/>

      if Ti has a X-lock on D
      then
         write(D);
      else begin
         if necessary, wait until no other transaction has any lock on D
         if Ti has a S-lock on D
            then upgrade the S-lock on D to X-lock
         else
            grant Ti a X-lock on D
            write(D);
      end

Implementation of Locking<br/>
-
lock manager - 별도의 프로세스로 구현 가능<br/>
Transaction - lock과 unlock 요청을 메시지로 보낼 수 있음<br/>
lock manager<br/>
1. lock 요청에 대한 응답으로,  승인 메시지 or Rollback(dead lock의 경우) 메시지를 보냄<br/>
   1. 요청한 트랜잭션은 응답 받을 때까지 기다림<br/>
2. in memory 구조인 lock table을 유지하며 부여된 lock 및 대기 중인 요청을 기록함<br/>

Lock table<br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ac941ff8-a6f3-4339-a227-5a14cbb344b6)<br/>

새로운 request - data item에 대한 request queue의 끝에 추가<br/>
unlock request - request가 삭제됨. 이후 request가 부여될 수 있는지 확인<br/>
If transaction aborts, 해당 T의 모든 waiting 및 granted는 삭제됨<br/>
1. lock manger - 각 T가 보유한 lock list를 유지 가능<br/>

Graph - based Protocol<br/>
-
2PL의 대안<br/>
DB item의 액세스 순서에 대한 사전 지식을 얻기 위해, 모든 data item의 set D = {d1,d2,d3...}에 부분 순서를 부여<br/>
di-> dj 이면, di와 dj를 access하는 T는 di를 dj전에 access해야 함<br/>
부분 정렬 -> directed acyclic graph (called database graph)<br/>
Tree protocol은 graph-based protocol의 simple 버전<br/>

Tree Protocol<br/>
-
오직 X-lock만 허용 <br/>
1. Ti의 첫 번째 lock은 any data item에 대해 가능<br/>
2. 그 후, Ti는 Q의 부모가 현재 Ti에 의해 잠겨 있는 경우에만 data Q를 잠글 수 있음(즉, 방금 처음 잠근 애의 child에만 lock 가능)<br/>
3. Data item은 언제든지 unlock 가능<br/>
4. Ti에 의해 잠기고 해제된 item은 나중에 Ti에 의해 다시 lock 불가<br/>

Graph-based Protocol<br/>
-
Tree protocol<br/>
1. conflict serializability 보장<br/>
2. deadlock 안 걸림 보장<br/>
3. unlock이 2PL보다 일찍 발생할 수 있음<br/>
   1. 짧은 waiting time<br/>
   2. deadlock이 없으므로 no rollback<br/>

단점<br/>
1. recoverability와 cascadelessness를 보장X<br/>
2. T는 access하지 않는 data item을 잠가야할 수 있음<br/>
   1. lock overhead 증가 및 추가 waiting time<br/>
   2. concurrency 감소<br/>
  
Tree protocol 에서는 conflict-serializable 가능하지만, Two-phase locking에서는 conflict-serializable 불가능 한 스케줄S가 존재할 수 있다.<br/>
반대 또한 가능하다.<br/>




