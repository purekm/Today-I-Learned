Concurrency Control1 <br/>
동시성 제어 정책은 허용 가능한 스케줄만 생성되도록 보장

Lock – Based Protocol <br/>
2가지 모드의 lock <br/>
1. shared mode - 읽기만 가능한 lock<br/>
2. exclusive mode - 읽기와 쓰기가 가능한 lock<br/>

트랜잭션 : concurrency - control mangaer에게 lock 요청 -> 요청이 승인된 후에만 트랜잭션이 진행될 수 있음<br/>
Concurrency-control manager : 락의 compatibility(호환성)에 따라 락을 부여할지 결정<br/><br/>
주어진 락 모드 A와 B에 대해<br/>
트랜잭션이 모드 B lock이 있는 data item Q에 모드 A lock을 즉시 부여받을 수 있다면?<br/>
-> mode A is compatible with mod B<br/>

Lock compatibility table<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/30b993f1-5bb1-4b81-951e-ac30d9e26c7f)<br/>

Exclusive lock을 사용하면 다른 lock은 못 들어옴<br/>
Shared lock 끼리는 compatible<br/>

Schedule with lock grants<br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/5fb31712-b082-4158-83b7-2c909679b86a)<br/>

T1과 T2를 동시에 스케줄링<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/a0fe4010-e059-4807-a219-06269fec30c3)<br/>
이전의 이미지와 비교했을 때, T1과 T2를 이렇게 동시에 사용하면, T1에서 A가 바뀌기 전에 T2가 A+B를 출력하여 일관성 문제가 발생<br/>


![image](https://github.com/purekm/Today-I-Learned/assets/90774046/404402f3-3c8d-4ca0-a57b-51368016e421)<br/>
해결 방법 - A와 B의 lock을 작업이 다 끝나면 해제해줌<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/8eb888f9-f258-4f79-a5d6-dbcbcb33c63a)<br/>
T3는 B에 대한 X-lock을 획득하고 B에대한 작업을 실행하고, T4는 A에 대한 S-lock을 획득하고 작업을 실행<br/>
T3에서 A에 대한 X-lock을 획득하려고 하는데, T4에서 S-lock을 해제하지 않았으므로 대기<br/>
T4에서도 B에 대한 S-lock을 획득하려고 하는데, T3에서 X-lock을 해제하지 않았으므로 대기<br/>
-> 무한 대기, 즉 deadlock 발생<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/81410e45-d3e2-400e-b1ca-1209a911492a)<br/>
위와 마찬가지로 Deadlock 발생<br/>



