Query Processing <br/>
1. query가 들어오면 relation-algebra로 바꾼다. <br/>
2. Optimizer로 최적화 – 같은 관계 대수 여러 개가 존재하지만, 통계적인 데이터를 사용해서 최적의 비용을 고름<br/>
3. Execution plan<br/>
4. Evaluation engine  어떻게 실행할지(인덱스) 정보 존재<br/>
<br/>
Measure cost – 디스크에서 블록 전송 수와 탐색 수를 비용 측정 요소로 사용한다.<br/>
Tt = time to transfer 1 block(assume write cost = read cost)<br/>
Ts = time for 1 seek(disk seek time + rotational latency)<br/>
Cost = T(t)*b + T(s)*S이다.<br/>
<br/>
Selection Operation<br/><br/>
	Using file scan<br/><br/>
1. Algorithm A1(linear search)<br/>
예상 비용 = br 개의 블록 전송 + 1 번의 탐색<br/>
기본 키 속성의 특정 값을 찾는 경우, 일치하는 레코드가 발견되면비용절감<br/>
Br/2 개의 블록 전송 + 1 번의 탐색 (평균적으로 중간에 있으므로 /2)<br/><br/>
      

Algorithm A2(clustering index, B+ tree) – using B+ tree and select search-key<br/>
예상 비용 = (트리 높이(root에서 leaf까지)+1(leaf에서 pointer를 얻고 transfer과 seek함))*(블록 전송 시간 + 탐색 시간)<br/>
Root~leaf까지 h번 + 리프 노드에서 실제 데이터 읽기 1번  h+1<br/>
(H+1)*(t+s)<br/><br/>
Algorithm A3(clustering index, equality on non-key) 연속된 블록에 위치한 여러 레코드 검색<br/>
여러 record를 검색할 것인데, 매칭되는 record는 연속된 블록에 위치할 것<br/>
B = 일치하는 레코드를 포함하는 블록의 수 라고 할 때, <br/>
Cost = hi*(블록 전송 시간 + 탐색 시간) + 탐색 시간 + 블록전송시간*b<br/>
인덱스 조회 h*(t+s)<br/>
첫 번째 데이터 블록 찾기 s<br/>
일치하는 레코드가 연속적인 블록에 위치하므로 b개의 블록을 순차적으로 읽는다. t*b<br/>
결론적으로 h*(t+s)+s+t*b<br/>
<br/><br/>
Algorithm A4(secondary index, on key)  <br/>
후보키로 지정된 검색키가 있는 경우 단일 레코드를 검색<br/>
Cost = (hi+1)*(T(t)+T(s)) A2과 Cost가 같다<br/><br/>

Algorithm A4(secondary index, non key) <br/>
검색 키가 후보 키가 아닌 경우 여러 레코드를 검색한다.<br/>
B+ 트리 인덱스 탐색 h 개의 t와 s가 발생<br/>
검색 키가 후보키가 아니므로, 여러 레코드가 일치할 수 있다. n개의 일치하는 레코드를 모두 찾으려면 각 레코드에 대해 t,s가 필요하다.<br/>
(H+n)*(t+s)<br/><br/>
Selections involving comparison<br/><br/>
A5 (clustering index, comparison)<br/>
A>=v인 record를 모두 구하려면 A>=v인 첫 번째 tuple을 찾고 거기서부터 순차적으로 찾는다<br/>
A<v인 경우에는 relation의 첫 번째 tuple부터 찾다가 멈춤(do not use index)<br/><br/>
A6 (secondary index, comparison)<br/>
인덱스를 찾고, 순차적으로 탐색하여 포인터를 찾음.<br/>
연속적인 포인터가 아니기 때문에, linear하게 읽는 게 빠를 수 있다.<br/>
리프노드를 스캔하여 A<=v인 레코드 포인터를 찾는다.<br/><br/>
A5와 A6의 차이점으로는 A5는 클러스터링 인덱스를 사용하여 레코드가 연속적인 블록에 저장되어 있고, A6는 보조 인덱스를 사용하기 때문에 레코드가 연속적이지 않을 수 있다.<br/><br/>
![그림2](https://github.com/purekm/Today-I-Learned/assets/90774046/17829791-830f-4793-a048-a2f4a1862f44)

Bitmap index Scan<br/>
어느 경우든지 최악은 아님<br/>
보조 인덱스를 사용하여 일치하는 튜플의 인덱스 항목을 찾는다. <br/>
비트가 1로 설정된 블록들을 순차적으로 스캔하여 데이터를 가져온다.<br/>
비트수가 적은 경우, secondary index scan과 유사한 성능<br/>
비트수가 많은 경우, 선형 파일 스캔과 유사한 성능<br/><br/>
Implementation of Complex Selections<br/><br/>
A7(conjunctive selection using one index) <br/>
가장 적은 비용으로 결과를 얻을 수 있는 조합과 A1~A6 중 알고리즘 선택<br/>
선택한 조합을 사용하여 record 검색<br/>
검색한 record를 메모리에 가져옴<br/>
메모리에 가져온 결과를 기반으로 다른 모든 조건을 test<br/><br/>
A8(conjunctive selection using a composite index)<br/>
적절한 복합 속성의 인덱스를 사용수 있는 경우에만 사용<br/><br/>
A9(conjunctive selection by intersection of identifiers)<br/>
포인터를 모아서 condition 만족하는 entry들을 찾고, 그 pointer들의 교집합을 구함<br/>
이후 포인터들의 block을 읽어 옴<br/><br/>
Complex Selections<br/><br/>
A10(disjunctive selection by union of identifiers)<br/>
인덱스가 있어야 pointer가 있으므로 사용할 수 있다.<br/>
그렇지 않으면 선형 스캔 사용<br/>
각 조건에 해당하는 인덱스를 사용하고, 얻어진 모든 레코드 포인터 집합의 합집합을 구함<br/>
이후 파일에서 레코드를 가져온다<br/><br/>
Selection involving Negation<br/><br/>
Equality 비교를 포함하는 경우, 데이터 파일에서 선형 스캔을 사용하여 조건에 맞는 레코드를 찾는다.<br/>
부정을 포함하지 않는 조건에 대해 인덱스를 사용할 수 있는 경우, 인덱스를 사용하여 조건에 만족하는 레코드를 찾을 수 있다. (Ex a!=5 이면 a>5 || a<5 로 변환 가능)<br/>
