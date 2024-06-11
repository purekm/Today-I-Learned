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
   트랜잭션을 커밋 순서로 직렬화 가능<br/>

대부분의 DB는 rigorous two-phase locking을 구현하는데, 걍 two-phase locking이라고 부름<br/>

Lock Conversion<br/>
-
트랜잭션이 실행 중에 특정 데이터 항목에 대한 lock을 변경할 경우<br/>
1. 데이터 항목을 읽기 위해 S-lock을 걸고, 데이터를 수정하기위해 X-lock으로 변경<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/775417a0-2992-42d7-b432-500eed3fb389)
<img width="367" alt="image" src="https://github.com/purekm/Today-I-Learned/assets/90774046/f4febae2-8d38-49ee-8886-e055ffbc147d">


규칙<br/>
1. X-lock으로 upgrade<br/>
   1. 트랜잭션이 Growth 단계에서만 가능<br/>
2. S-lock으로 downgrade<br/>
   1. 트랜잭션이 Shrinking 단계에서만 가능<br/>

Two-phase protocol을 사용하면서 lock conversion을 적용하면 conflict serializability를 보장

더 많은 동시성 가능해짐
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/79c7ab35-a0a0-445f-9fd3-5f3256261e32)
lock conversion

