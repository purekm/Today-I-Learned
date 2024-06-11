//미검토상태

가상 메모리
-
1. 전체 프로그램이 다 필요하진 않으므로, 일부분만 사용 <br/>
2. 일부만 로딩하니까 memory의 한계에 제약 받지 않음 <br/>
3. I/O가 작아서 빠르게 돌아감 <br/>
4. 논리적인 메모리를 물리적인 메모리보다 많이 할당 가능 <br/>
5. 공유가 쉬움 <br/>
6. 프로세스 생성이 효율적 <br/>
7. 동시에 돌리기 가능하고, I/O가 적게 필요 <br/>

가상의 주소라서 0번부터 끝까지 사용 가능 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/f5088fdf-0830-4996-aca3-659cb46a4cf0) <br/>

hole에 공유 library or 공유 메모리가 들어감 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1b19da50-5c11-4c1e-98b5-bb20be8cef45) <br/>

Demand paging - 필요한 페이지만 가져오는 것 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c9cb3485-0898-4b04-8c1e-993179a888d1) <br/>

주소 변환 과정에서 Invalid bit가 i로 설정되어 있으면 page fault가 발생 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/5beb0f30-3c41-4e0c-bc16-c4c32de8205d) <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/71af5be2-d6d9-452e-b08e-aafee0205233) <br/>

Steps in Handling Page Fault <br/>
-
1. 페이지 참조 <br/>
   1. 만약 프로세스가 특정 페이지를 참조하고, 그 페이지가 현재 메모리에 없을 경우 해당 참조는 os에 의해 trap으로 처리 <br/>
2. 운영 체제의 결정 <br/>
   1. 운영체제는 페이지 참조가 유효한지 판단 <br/>
   2. 주소 범위 밖을 참조하면, 프로세스를 중단 <br/>
   3. 페이지가 메모리에 없는 경우, 페이지 fault 처리를 진행 <br/>
3. free frame 찾기 <br/>
4. 페이지 swap <br/>
5. 테이블 update <br/>
6. 명령어 재시작 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c3bec95d-2542-4ddd-89b0-6a4aa163e59f) <br/>

1번 진행하려고 하는데 M이 page memory에 없네?? <br/>
1번 page table에서 찾으려는데 invalid 하므로 interrupt를 발생시켜 제어권을 os에게 넘김 <br/>
2번까지는 user mode이고, 이후에는 kernel 모드 <br/>
3번에서 backing store로 가서 빈 frame 자리 찾고, (4번) backing store에서 페이지를 가져온 후, 빈 frame에다가 넣음 <br/>
5번에서는 옮겨온 페이지의 frame 번호를 page table에 저장하고, 업데이트 <br/>
6번에서 마지막으로 restart instruction <br/>

4번 과정이 진행될 때, 디스크는 매우 느리기 때문에 context switching이 되어서 다른 process가 일하고 있음 <br/>
I/O가 끝나면 ready queue에 넣어주고나서 자기 차례가 되면 실행 <br/>
이후에 원래 interrupt가 걸린 곳으로 돌아온다. <br/>

Major page fault - 페이지가 메모리에 없는 경우 발생 <br/>
Minor page fault - 페이지가 메모리에 있지만 매핑이 안 되어 있는 경우(공유 라이브러리), 또는 원하는 페이지가 free-frame 리스트에 아직 남아 있는 경우 발생 <br/>

pure demand paging - 시작할 때 아무런 페이지가 없으니까 fault가 자주 발생 <br/>
-> prepaging으로 메모리에 일부를 미리 로딩시킴(드물지만 한 명령어에 4번의 fault 발생 가능) <br/>

Demand paging 하려면 Hardware support 필요 <br/>
1. Page table with valid/invalid bit <br/>
2. Secondary memory (swap space) <br/>
3. instruction restart <br/>

Instruction restart <br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c28bde13-d772-4d6e-8b97-7a5df8cb26df) <br/>
이런 경우에는 fault가 일어났을 때 restart해도 문제가 생김(원본이 깨짐) <br/>

Solution
1. 페이지 fault가 일어나기 전에 미리 페이지를 불러들이고 명령어를 실행 <br/>
2. 임시 레지스터에 겹치는 부분을 저장했다가 page fault 발생 시 restore <br/>

Page fault 상세 과정 <br/>
-
1. Trap to OS <br/>
2. Interrupt가 발생했으므로, register와 state를 저장하고 감 <br/>
3. Interrupt의 원인이 page fault인지 확인 <br/>
4. 페이지 조회가 유효한지 확인하고, 디스크에서 해당 페이지의 위치를 파악 <br/>
5. 메모리에서 빈 공간을 찾아서 메모리로 읽어 옴 <br/>
   1. request가 발생하면, disk에 request queue에 들어가서 조금 있다가 실행됨(디스크 내부에서 순서가 나름 최적화됌) <br/>
   2. device 탐색 및 대기 시간 발생 <br/>
6. 5번을 기다리는 동안, CPU는 다른 프로세스에게 넘어감 <br/>
7. I/O가 종료되면 interrupt가 걸려서 실행 중인 프로세스를 중단시킴 <br/>
8. 따로 실행되었던 프로세스의 레지스터와 상태를 저장하고 종료됨 <br/>
9. Interrupt가 디스크의 request였는지 확인 <br/>
10. Page table 정리 <br/>
11. Process가 ready queue에 넣어지고, 스케줄러에 CPU제어권을 넘겨줬으므로 CPU할당을 기다림 <br/>
12. Interrupt를 받았던 장소로 돌아와서 저장했던 register와 state 복구 <br/>

Free Frame list <br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b81d10da-d407-403e-a16b-cfbf585fbbbb) <br/>
Free frame을 사용할 때, 안에 있는 데이터를 지우고 줌(zero-fill-on-demand) <br/>
어느정도 임계치(꽉 채우지 않음)까지 찬다면, 채워져 있던 칸을 빼앗아옴 <br/>
만약 뺐어왔는데 변경했다면(dirty bit) 변경한 내용을 backing store에 저장하고 free frame list로 옮김 <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/32e1a461-4c2f-45dd-99fe-74508b4573a8) <br/>
변경된 애들을 저장하는 modified frame list에 모아두고, 나중에 쓰게되면 free-frame list로 옮김 <br/>

Backing store에 데이터를 저장하는 것은 비용이 많이 듦 <br/>
1. Free frame에서 하나를 가져와서 modified frame에 있는 애들을 압축해서 넣음 <br/>
2. 압축해서 free frame에 저장했으니까, 저장한 애들은 free-frame list에 올려도 되고 굳이 backing store에 저장할 필요 없음 <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/36fe4943-b605-48ce-95d2-9ba80335dc37) <br/>
7번은 free frame list에서 빠졌지만, 압축한 3개가 free frame list로 옮겨짐 <br/>
Android와 IOS에서는 swapping이나 paging을 쓰지 않고 memory compression을 사용 <br/>

Performance of Demand Paging <br/>
-
Three major activities <br/>
1. Service the interrupt <br/>
2. Read the page <br/>
3. Restart the process <br/>

Page Fault rate 0<=p<=1 <br/>
if p = 0 -> no page fault <br/>
if p = 1 -> all fault <br/>

Effective Access Time(EAT) <br/>
EAT = (1-p)*memory access + p(page fault overhead + swap page out + swap page in) <br/>

Example <br/>
Memory access time = 200ns, average page fault service time = 8ms = 8000000ns <br/>
EAT = (1-p)*200+p*8000000ns = 200+p*7999800 -> EAT 는 p에 비례 <br/>

Demand Paging Optimization <br/>
-
Swap 공간은 파일 시스템보다 빠르기 때문에 swap space 사용 <br/>
변하지 않는 binary 이미지는 파일 시스템에 읽어오고, 프로그램 실행하면 새로운 정보들이 생기는데 <br/>
이런 정보들을 anonymous memory라고 부르고 swap space 사용 <br/>

Copy on write <br/>
-
카피한 것 처럼 페이지를 공유 <br/>
Vfork() 실제로 복제하지 않고 링크만 가져옴 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/8752976b-b1e2-4785-a896-eb8a0e3b4cba) <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ceb26f4e-6d4a-4c76-b119-7a5cceee0f89) <br/>



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
프레임안에 있는 숫자 중 가장 늦게 사용하는 숫자를 교체
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













