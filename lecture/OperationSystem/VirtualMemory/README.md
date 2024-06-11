//미검토상태



Free Frame 자리가 없으면 어떻게 해야하나? <br/>
-> free frame이 없다는 말은 메모리가 꽉 찼다.<br/>
페이지 교체 - 메모리에 있지만, 잘 사용하지 않는 페이지를 내보냄<br/>
데이터를 불러왔을 때랑 비교했을 때 값이 변경된다면 backing store에 저장해야함 <br/>
-> 당연히 dirty bit이 안되어있는 애를 부르는게 편함 <br/>
누구를 내보낼지 판단할 때 dirty bit도 관여를 함<br/>

페이지 교체 <br/>
페이지를 불러오는데, 메모리를 불러와야하는데 메모리 공간이 없으면 victim frame을 찾아야함<br/>
victim frame이 dirty 하다면 backing store에 저장해야줘야 함<br/>
이후 page fault가 일어나지 않도록 update를 해줌<br/>

page fault에서 page transfer은 잠재적으로 2번<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/caac58a4-f610-4fab-b84a-57f5a15dc50f) <br/>

O를 찾았는데 invalid라서 f를 victim frame으로 찾음 (자기 page를 희생 - local page replacement)<br/>

f를 희생시켰으므로 f는 invalid가 되고 O는 f가 되어 valid로 바뀜 ( O | i -> f | v) <br/>

페이지 교체 알고리즘 <br/>
-
reference string -메모리를 조회할 때 조회하는 페이지를 string으로 나타낸 것 <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/218a5d23-4396-4c1d-89c6-f20debcbc8d3) <br/>
reference string은 페이지 교체 알고리즘의 효율을 평가하는데 좋음 <br/>

페이지 교체 알고리즘이 결정해야할 것<br/>
-
1. 프로세스 당 몇개의 프레임을 할당하는가?<br/>
2. 어떤 프레임을 교체하는가?<br/>

프레임을 늘리면 페이지  폴트가 감소하는 일반적인 모습 <br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1dfcfdb8-ad90-47ee-b3ce-9c5292eb2bc4) <br/>


FIFO Algorithm <br/>
-
가장 먼저 들어온 순서대로 페이지 교체<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7c6b5223-f750-4c1e-8d68-fb70474ee00d) <br/>

프레임을 늘리면 페이지 fault가 일반적으로 감소한다고 말했었는데, 항상 그렇지는 않음 <br/>
-  
1. Belady's Anomaly <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/5d5e21d1-f107-4f26-b42f-a5b30447dbdf) <br/>
이런 현상이 일어나면, 좋은 알고리즘은 아니라는 의미

Optimal Algorithm <br/>
-
미래에 어떤 걸 사용하는지 알아야 하므로 구현하기 어렵긴하다... <br/>
FIFO에서는 15번의 page fault가 일어났지만, Opt 에서는 9번의 page fault <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7a86c852-e356-4902-b9aa-436b6fa5f244) <br/>
만약 reference string을 거꾸로 뒤집어서 적용해도 page fault가 똑같이 나옴 <br/> 

LeastRecentlyUsed(LRU) Algorithm <br/>
-
가장 오래전에 사용했던 페이지를 교체 <br/>
FIFO에서는 15번, Opt에서는 9번, LRU에서는 12번의 page fault 발생 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/67d4362d-9962-4113-b6af-77e939e33e40) <br/>
근사치를 사용하여 구현함 <br/>
OPT 알고리즘과 유사하게, 거꾸로해서 page fault를 세어봐도 page fault의 수가 같음 <br/>
현대 페이지 교체의 major pick <br/>

LRU 구현 방식 <br/>
-
Counter 방식 <br/>
시계처럼 돌아가는 방식으로 옛날에 사용한 것을 찾음 <br/>
Stack 방식
Stack이므로 마지막에 사용했던게 젤 위에 있음 <br/> <br/>
이 두 방식을 hardware 도움 없이 software로만 한다면 10배 이상 느려짐

LRU와 OPT는 stack algorithms을 따르기 때문에 Belady's Anomaly를 가지지 않음 
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b56d945d-58cf-4c7e-a19b-1e0f64022a0d) <br/>
a이후에 7을 access 했는데, 스택안에 아래에 있던 7이 top으로 올라옴 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6d5cd89a-499d-49e2-8812-3db5def1c490) <br/>

LRU Approximation Algorithms <br/>
-
hardware의 도움을 받아서 LRU하는 버전<br/>
1. Reference bit<br/>
   1. 처음에 bit = 0으로 설정<br/>
   2. 최근에 page를 참조했으면 1로 변경<br/>
   3. 주기적으로 reference bit을 0으로 초기화 해줌(나중에 순서를 모르겠지만 어쩔 수 없음)<br/>
2. Second-chance algorithm<br/>
   1. Clock replacement<br/>
   2. 1이면 기회를 한번 주고, 0이 나감<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/05fbbb3a-0055-4e3c-9a95-69c25a294390)<br/>
3. Enhanced Second-chance algorithm<br/>
dirty bit까지 사용<br/>
dirty bit이 1이면 변경되었다는 의미니까 내보내기 힘듬<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/cb5f68aa-d3ef-4ef4-8c24-e7650a0651e4)<br/>
가장 만만한게 (0.0)<br/>

reference bit이 1이면 사용되었다는 사실만 알고, 언제 되었는지는 모름 <br/>

4. Additional reference bits algorithm  <br/>
Timer interrupt를 통해 주기적으로 OS가 오른쪽으로 한 비트씩 이동시킴 <br/>
과거의 행적을 알 수 있는 장점이 있음 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/e6194507-cf39-4004-a733-fcc46459aa5c) <br/>

5. Demand paging and reference bit <br/>
Demand paging은 필요할 때 페이지를 불러오기 때문에 reference bit을 1로 세팅 <br/>
페이지를 불러오고 나서 Second-chance 알고리즘처럼 할 수도 있고, 주기적으로 모든 reference bit을 0으로 reset해버림  <br/>

Counting Algorithms  <br/>
-
구현이 비싸고 , OPT에 근접하지 못함 <br/>
페이지 접근 빈도수로 결정 <br/>
Least Frequently Used Algorithm(LFU)  <br/>
Most Frequently Used Algorithm(MFU) <br/>

Page-Buffering Algorithms <br/>
-
Pool을 사용하여 page fault 시간(누구 거를 교체할거냐 find 시간)에 찾지 않고 바로 할당 <br/>
Pool을 사용하면 victim 스왑 공간을 쓰는것 과 병행 실행 가능하다. <br/>

변경된 페이지를 paging device가 놀때, store에 써놓으면 시간 절약 가능 <br/>
free frame의 내용이 backing store과 같으면 재사용 가능 (원래는 지우고 줌) <br/>

Applications and Page Replacement <br/>
-
DBMS는 앞으로 어떤 일을 할지 자기가 알 수 있어서, 자기가 관리를 함  <br/>
DBMS 처럼 스스로 메모리와 I/O 버퍼를 관리하는 경우, double buffereing 현상이 발생할 수 있음 <br/>

raw disk mode 읽어봐 <br/>

Allocation of Frames  <br/>
-
프로세스마다 몇개의 frame을 할당할거야?<br/>
minimum과 maximum 개수가 존재<br/>
CPU마다 달라질 수 있음<br/>

Maximum of frames<br/>
1. fixed allocation<br/>
   1. Equal allocation - 균등 할당 <br/>
   2. Proportional allocation - process의 크기에 따라서 할당<br/>
      1. ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/bc151598-7aa0-4859-bf50-8b327d25ae1a)<br/>

3. priority allocation<br/>

Global vs Local Allocation
1. Global - 전체 중에서
2. Local - 자기꺼 에서













