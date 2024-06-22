Query Processing 3

Join operation<br/>
-
1. equal-join<br/>
2. natural-join<br/>
3. Theta-join<br/>

여러가지 알고리즘으로 조인 구현<br/>
1. nested-loop join<br/>
2. block nested loop join<br/>
3. indexed nested loop join<br/>
4. merge join<br/>
5. hash join<br/>
-> 비용에 따라 선택<br/>

Nested-Loop Join<br/>
-
중첩 루프 조인 알고리즘<br/>
r의 각 레코드에 대해 s를 완전 스캔<br/>
r - outer relation<br/>
s - inner relation<br/>
인덱스 필요 X - 어떤 종류의 조인 조건에서도 사용 가능<br/>
Expensive - 두 릴레이션의 모든 튜플 쌍 검사<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/56bed9ac-70a7-4bc5-8869-eedbe70b6050)<br/>

nr = r에 있는 튜플 수<br/>
bs,br = s와 r의 튜플을 포함하는 블록 수 <br/>

최악의 경우 - 버퍼에 각 릴레이션의 블록 하나만 담을 수 있을 때<br/>
1. block transfer - nr*bs + br<br/>
2. seek - nr + br <br/>

최상의 경우 - 두 릴레이션이 메모리에 딱일 때<br/>
1. block transfer - br + bs<br/>
2. seek - 2<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/3fcd43a1-32f4-4f91-b896-4199b2aa8513)<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/99ab8683-45e6-4059-84fd-c0bf2dbe4431)<br/>

Block nested - loop join<br/>
-
블록 단위로 nested loop join <br/>
최악의 경우 - 어떤 릴레이션도 메모리에 맞지 않을 때<br/>
1. block transfer - br*bs + br<br/>
2. seek - 2br<br/>

최상의 경우 - inner 릴레이션이 메모리에 맞을 때<br/>
1. block transfer - br+bs<br/>
2. seek - 2<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/e6f369f8-e220-4321-b4e2-40d6f61c2499)

최상의 경우에는 전부 block transfer - br+bs , seek - 2??<br/>

Indexed Nested loop join<br/>
-
오직 equal-join과 natural join 에서만<br/>
inner relation의 조인 속성에 인덱스가 있어야 함<br/>

outer relation r 의 각 튜플 tr에 대해, 인덱스를 사용 -> 조인 조건 만족하는 s의 튜플 조회<br/>
-> s에서의 selection과 같음<br/>

최악의 경우 - 버퍼에 r의 오직 한 page 공간만 있음<br/>
cost - br(tr+ts)*nr*c<br/>

r과 s의 조인 속성에 인덱스가 있는 경우에는 튜플 수가 적은 릴레이션을 outer relation으로 사용하여 비용을 줄임<br/>

Merge-Join <br/>
-
equal-join과 natural join에서만 사용 가능
릴레이션 r과 s가 조인 속성으로 정렬되어 있다고 가정
각 블록은 1번만 read

알고리즘
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1e4aa55e-fda1-42c2-9430-da8d85640e96)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/db2bf8ea-8b79-4da8-90bf-414ea163af6f)

pr을 내리면서 확인해봄

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/eefaae45-1bd3-42b0-a4b7-45c0264ad1ad)

Hash Join <br/>
-
eqaul join과 natural join에서 사용 가능

Hash 함수 h로 사용 -> 두 릴레이션의 튜플 분할
h(


