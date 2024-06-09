Transaction 2<br/>
스케줄은 동시에 실행되는 트랜잭션 명령들의 실행 순서<br/>
하나의 스케줄은 해당 트랜잭션들의 모든 명령을 포함해야함<br/>
1. 트랜잭션 간의 데이터 충돌을 촤소화<br/>
2. 각 트랜잭션이 데이터베이스의 일관성 유지<br/>
3. 자원을 효율적으로 사용하여 시스템 성능 향상<br/><br/>

Serializable 스케줄<br/>
1. 직렬 스케줄과 결과가 동일한 스케줄 – 일관성을 보장하는데 유용함 <br/>
2. 병렬로 실행되지만 결과가 직렬 스케줄과 동일한 스케줄<br/><br/>

Conflict Serializability<br/>
1. 두 스케줄이 각 트랜잭션의 연산 순서를 보존하면서 서로 변환 될 수 있는 경우<br/>
2. 동일한 데이터 항목에 대한 읽기와 쓰기, 쓰기와 쓰기 연산 순서가 같아야함<br/><br/>

View Serializability<br/>
1. 각 트랜잭션이 읽는 값과 최종 결과가 동일할 경우<br/><br/>

View Serializability <br/>
1. 스케줄 S에서 Ti가 Q를 읽고 그 값이 Tj에의해 생성된 값이라면 스케줄 S’에서도 동일한 쓰기 연산에 의해 생성된 Q를 읽어야 한다. <br/><br/>

![그림3](https://github.com/purekm/Today-I-Learned/assets/90774046/6b5c8633-2f66-4b71-960f-62cb936168ba)

두 명령어가 동일한 데이터 항목 Q를 액세스 하는데, 둘 중하나가 write인 경우 무조건 conflict 발생<br/>
1. Conflict가 발생하면, 논리적 시간 순서가 강제됨<br/>

S에서 I와 J가 충돌하지 않는 명령어라고 할 때,<br/>
S’에서 J 와 I 순서로 실행한다고 하면, 충돌 동등하다.<br/><br/>
충돌 직렬 가능성<br/>
1. 직렬스케줄과 충돌 동등하다.<br/><br/>
![그림4](https://github.com/purekm/Today-I-Learned/assets/90774046/8facb844-c45f-456b-9fa5-fbc5e7ad51ef)

모든 충돌 직렬 가능한 스케줄은 뷰 직렬 가능하다. 하지만 모든 뷰 직렬 가능한 스케줄이 충돌 직렬 가능한 것은 아니다.<br/>
