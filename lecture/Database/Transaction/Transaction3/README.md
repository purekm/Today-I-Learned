Transaction 3<br/>
 ![그림5](https://github.com/purekm/Today-I-Learned/assets/90774046/ada6a79d-310c-4f49-b9e5-dc8582dcad47)

T7은 T6에서 write 한 값을 read를 하고 commit을 통해 작업을 확정했다.<br/>
하지만 만약 T6가 commit에 실패를 한다면, T6은 abort되어 rollback되어야 하는데<br/>
T7은 이미 그 값을 read했다. 그러면 T7의 값도 abort해야하는데, 이미 commit을 해버린 상태라서 회복 불가능한 상태가 되어버렸다.<br/>
 ![그림6](https://github.com/purekm/Today-I-Learned/assets/90774046/53b12f39-6920-4c88-91f8-dac2cd852632)

만약 T8이 commit을 fail 한다면 연쇄적으로 rollback 되는 상황 <br/>
매우 비효율적인 상황 발생<br/>
![그림7](https://github.com/purekm/Today-I-Learned/assets/90774046/1339faef-1424-4e7a-b395-dcf4550d2484)

 
각 transaction이 작업을 마치고 commit으로 작업을 확정했기 때문에,<br/>
Rollback이 연쇄적으로 일어나지 않는다. 시스템 복구에 용이함.<br/>
모든 비연쇄 스케줄은 회복가능하다.<br/><br/>

Serializability<br/>
데이터의 일관성 유지를 위해 직렬화 사용(순차적 실행과 동일한 결과)<br/>
1. 직렬가능성을 보장하기위해 프로토콜이 너무 적은 동시성 허용 가능<br/>
2. 일부 app에서는 더 약한 일관성 수준을 사용하여 직렬화 되지 않는 스케줄 허용<br/>
   1. 동시성을 높이고 성능개선 가능<br/><br/>
   
Serializable <br/>
1. 일부 데이터베이스 시스템은 이 격리 수준을 구현할 때, 특정 비직렬 가능한 실행 허용 가능<br/>
2. 트랙잭션 간 상호작용을 완전히 차단하여 데이터 일관성 최상<br/>

Repeatable Read – commit된 데이터만 읽을 수 있고, 동일 transaction 내에서 동일 데이터를 반복해서 읽으면 항상 같은 값 반환<br/>
1. 다른 transaction과 직렬화 되지 않을 수 있음<br/>

Read Committed – commit된 데이터만 읽을 수 있고, 반복해서 읽을 때는 다른 값을 반환가능<br/>
1. 연속적으로 읽을 때 서로 다른 값을 반환할 수 있음. <br/>
2. Commit된 데이터만 읽을 수 있도록 보장하지만, 동일 transaction내 읽기 작업에서는 일관성이 유지되지 않을 수 있음.<br/>

ReadUncommitted – commit 되지 않은 레코드도 읽을 수 있음<br/>
1. 데이터 일관성에 대한 최소한의 보장만 제공하며, 더티 리드가 발생가능<br/>

모든 isolation level 에서는 더티쓰기를 금지한다. – 커밋되지 않은 데이터 항목에 다른 transaction이 쓰기를 허용하지 않음<br/>
