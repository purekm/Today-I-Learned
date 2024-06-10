Concurrency Control1 <br/>
Lock – Based Protocol <br/>
	Shared mode<br/>
	읽는 건 가능 S mode<br/>
	Exclusive<br/>
	읽고 쓰는 거 전부 lock X mode<br/>
락은 모드 별로 compatible 한가?<br/>
특정 아이템에 대해서 어떤 트랜잭션이 B 모드 락을 얻었다고 하면 다른 트랜잭션이 A모드에 대해서 락을 얻을 수 있으면 A와 B는 compatibility(호환성) 하다.<br/>
Compatibility는 table로 나타낼 수 있다.<br/>
 
Exclusive lock을 사용하면 다른 lock들은 못 들어옴<br/>
Shared lock 끼리 compatible 하다. <br/>
 
T2는 동시에 써도 가능할 것 같은..?<br/>
 
B에서 50달러 빼서 A에 넣으려고 하는데<br/>
A에는 넣어지지 않은 상태로 read하고 연산을 진행해서  일관성이 깨짐<br/>
Unlock(B)을 너무 빨리해서 문제가 생긴 것. 해결 방법은 예시로 나옴<br/>
  데드락 발생<br/>
