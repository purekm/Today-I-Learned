메모리 관리하는 법 알기 <br/>
메인 메모리와 register는 CPU가 직접 접근할 수 있는 저장 공간 <br/>
Register은 1 CPU clock에서 접근 가능하기 때문에 접근이 빠름<br/>
Main memory는 접근이 느림 -> memory stall이 발생가능<br/>
1. Cache를 중간에 둬서 효율을 높임<br/>
메모리는 공유하고 있기 때문에 서로 침범하지 않게 보호해야 함<br/>

프로세스가 자신의 주소 공간 내의 주소에만 접근할 수 있도록 보장해야 하므로, 프로세스가 다른 프로세스의 메모리 영역에 접근하지 못하도록 해야함.<br/>
이를 위해 base register과 limit register 한쌍을 사용한다.<br/>

base register - 프로세스의 논리 주소 공간의 시작 주소<br/>
limit register - 프로세스의 논리 주소 공간의 크기<br/>

논리 주소 공간이 뭐야?<br/>
논리 주소 공간은 프로세스가 접근할 수 있는 메모리의 범위로, base register와 limit register를 사용하여 이 범위를 정의함 <br/>
base는 논리 주소 공간의 시작 주소 이고, base + limit 은 논리 주소의 시작과 끝 <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/2d1dba31-94e7-4250-bbff-91df482b19f4) <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1c007f02-d79d-4d89-a264-0017e9414868) <br/>

CPU는 매 접근마다 memory를 접근하는지 base와 base+limit을 통해서 확인한다. <br/>
만약 bases <= address < base+limit 이면 memory안에 있다는 사실을 알 수 있다.<br/>
base와 limit register를 설정하는 명령어는 권한이 있어야 하므로, 운영체제는 설정할 수 있지만 사용자 프로그램은 변경할 수 없다.<br/>

Address Binding<br/>
-
프로그램이 실행되려면 주소가 필요한데 주소는 언제 결정해?<br/>

주소 표현의 단계별 변화<br/>
1. Source code 레벨에서는 정확한 주소가 없고, 정보가 기호로 되어있음<br/>
2. Compiled 레벨에서는 relocated address를 사용(재배치 가능한 주소/상대적 주소)<br/>
3. Linker or Loader를 통해서 상대적인 주소를 절대 주소에 bind<br/>

Compile time - 메모리 위치가 알려진 경우, binding을 하면 절대 주소가 생기는데, 만약 로딩해야하는 위치를 옮기고 싶으면 recompile을 해야한다.<br/>
   1. 그러므로 Compile time에는 binding을 하지 않음<br/>
   2. Load time - 메모리 위치가 알려지지 않은 경우 relocateable code는 상대적인 주소이기 때문에 loading되는 순간 address에 대한 계산을 통해 실제 address를 알 수 있다.<br/>
   3. Execution time - 프로세스가 실행 중 다른 메모리 위치로 이동할 수 있는 경우에 실행시간에 binding이 이루어진다. Runtime 전까지 binding이 지연될 수 있고 hardware의 지원이 필요하다.<br/>
프로세스는 실행 중에 swaping , paging이 발생하여 움직일 수 있음<br/>

1. 실행 전까지 움직인다는 말은 가상 주소 사용을 의미함<br/>
2. 실행될 때 실제 physical 주소를 사용함<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/9a31d00f-fe8a-487f-bc22-233163cab2b7)<br/>
실행할 때 library를 link 하는 것 - dynamic linking<br/>
논리적인 주소 - CPU가 생성하는 주소<br/>
실제 주소 - 메모리 유닛이 보는 주소<br/>
Compile time 과 load time의 address는 logical address를 사용<br/>
실제로 실행될 때 주소가 결정되는데, 그때 주소가 physical address<br/>
logical address와 physical address는 서로 다를 수 있음.<br/>
Memory management에서 logical address를 physical address로 바꿔주는데, 이때 physical address는 CPU도 모르고 나도 모름.<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1aefc4e4-5c91-4c60-800f-d9a6a8b37dd1)<br/>
사용자 프로그램은 logical address를 사용할 뿐, physical address는 모름.<br/>

Dynamic Loading<br/>
-
1. 프로그램을 전부 로딩하지 않고, 필요할 때 로딩<br/>
2. Routine은 호출하기 전까지 로딩하지 않음<br/>
3. Memory space의 효율성이 좋고, unused routine은 로딩되지 않음<br/>
4. 모든 routine은 재배치 가능해야하고, 어느 위치로 가도 사용 가능해야 함<br/>
5. Library를 통해 쉽게 구현 가능<br/>

Static Linking
-
library 형태로 존재하는 것을 불러서 연결시키는데, binary program image로 직접 불러오는 방식<br/>
libary 코드가 실행 파일에 포함되서 크기가 클 수 있음 <br/>
실행 파일은 독립적으로 실행될 수 있지만, 모든 필요한 library를 포함해야 함 <br/>

Dynamic Linking
-
실행 시간까지 link가 연기되어, 필요한 library를 실행 중에 결합<br/>
그러다 보니 메모리에 상주하는 코드의 위치 정보를 가지고 있는 stub이 존재<br/>
stub은 루틴의 주소로 대체되어, 루틴을 실행<br/>
OS는 필요한 라이브러리가 메모리에 없으면 이를 load 해주고, 이미 있는 경우 이를 사용
공유 메모리에 넣어서 쓰면 메모리가 절약되지 않을까?<br/>
-> Dynamic Linking은 library에 유용한데, 이를 shared libraries라고 함<br/>

Dynamic loading과 달리 dynamic linking과 shared libraries는 OS의 도움이 필요<br/>

Contiguous Allocation<br/>
-
메모리를 할당할 때 필요한 메모리를 연속적으로 할당 (옛날방식)<br/>
메모리는 partition될 수 밖에 없음 <br/>
1. OS는 low memory에 있고, user process는 high memory에 있음<br/>
2. 각 프로세스는 논리적으로 연속적인 메모리 내에 있어야 함(물리적이진 않을 수 있음)<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ad1c4ba9-5d17-4ff6-bd69-531237717f8b)<br/>
논리적 주소가 limit register 범위 내에 있다면, relocation register을 통해 logical address를 physical address로 변환 <br/>

Variable Partition<br/>
-
Multiple-partition allocation<br/>
1. 동시에 실행할 수 있는  프로세스의 수는 메모리에 할당된 partition의 수에 따라 결정됨<br/>
2. 메모리 할당의 효율성을 위해 partition의 크기가 가변적<br/>
3. Hole - 사용 가능한 메모리의 블록으로, 다양한 크기의 hole들이 메모리 전반에 흩어져 있음<br/>
4. 프로세스가 도착하면, 해당 프로세스를 수요할 수 있을 만큼 큰 hole에서 메모리가 할당된다. 알아서 적절한 크기의 홀에 할당됨<br/>
5. 프로세스가 종료되면, 해당 partition이 해제되고 인접한 자유 partition은 하나의 큰 partition으로 결합됨<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/11560642-c0f2-45d6-b470-4d8d678be6dd)<br/>

Dynamic Storage-Allocation Problem<br/>
-
First-fit – 처음 hole에 충분히 크게 할당<br/>
Best-fit – 충분한 크게 중 젤 작은 거 할당 (정렬이 필요할 수 있음)<br/>
Worst-fit – 가장 큰 hole에 할당<br/>

First-fit이 일반적으로 가장 빠름 Why?? -> 탐색 시간이 짧고, 복잡한 정렬 과정이 필요 없기 때문에 빠름<br/>

Fragmentation <br/>
-
Externel Fragmentation - 전체 메모리 공간에 충분한 여유 공간이 필요하지만, 그 공간이 연속적이지 않은 경우 <br/>
1. 충분한 메모리 공간이 있음에도 요청을 만족시키지 못하는 경우 발생<br/>
Internal Fragmentation - 할당된 메모리 공간이 요청된 메모리 공간보다 약간 큰 경우, 그 차이가 실제로 사용되지 않는 메모리 공간이 되는 현상 <br/>
1. 사용하지 않는 공간이 생겨, 메모리 효율이 떨어짐<br/>

First-fit의 경우, 50% 법칙이 존재<br/>
First-fit에서 N개의 블록이 할당되면 약 0.5N개의 블록이 조각으로 떨어져서 전체 블록 수는 N+0.5N<br/>
사용되지 않은 블록 비율은 0.5N/1.5N = 1/3 으로 전체 메모리의 1/3이 조각나서 사용할 수 없게 됨<br/>

Fragmentation이 발생하면 못 쓰는 메모리가 많아짐 -> Compaction으로 조각들을 모음<br/>
메모리 contents들을 하나의 큰 block으로 만들어서 저장<br/>
Compaction은 실행 중인 코드를 옮길 수 있어야 가능<br/>

하지만 모든 상황에서 옮길 수 있는 것은 아님<br/>
I/O의 경우, 실행 중에 compaction을 하게 되면 버퍼의 위치가 변경되서 문제가 발생할 수 있음 -> I/O를 OS 버퍼에서만 수행 <br/>


Backing store도 항상 fragmentation 문제를 가지고 있음<br/>
Variable Partition에서는 Externel Fragmentation이 일어날 가능성이 많음<br/>
연속적인 메모리 때문에 사용했는데, physical 공간은 반드시 연속적일 필요가 없음 -> Paging을 사용해서 고정된 사이즈로 자름<br/>

Paging<br/><br/>
-
고정된 사이즈로 자르면 External Fragmentatiton을  최소화 할 수 있음<br/>
Physical address의 연속적이지 않은 특성도 이용 가능<br/>
1. 메모리를 자를 때 동일한 규격으로 자름<br/>
2. 논리적인 메모리를 동일한 크기로 자를 땐 page라고 부름<br/>
3. 물리적인 메모리도, 같은 크기인데 frame이라고 부름<br/>
   1. 크기는 2의 거듭제곱으로, 512bytes~16Mbytes<br/>

Mapping에 관한 정보는 page table에 있음<br/>
1. 논리적인 page number을 physical한 page frame으로 바꿔주는 정보가 있음<br/>

Internel fragmentation은 여전히 발생<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/43e8ef12-3ee6-4e8f-afe0-8a0fd86754d3)<br/>
Address의 크기는 2^m, page의 크기는 2^n<br/>
논리적인 주소와 page의 크기가 주어지면 Page number와 page offset을 알 수 있음<br/>
논리적인 주소가 16비트이고, 페이지의 크기가 4KB(2^12) 인 경우, 상위 4비트는 논리적인 주소, 하위 12비트는 페이지 offset을 나타냄 <br/>

모든 프로세스는 각자의 페이지 테이블을 가지고 있고, 논리적인 주소는 p와 d로 구성되어 있음<br/>
P는 page table의 index에 해당하는데, 해당 index에 가면 frame number을 나타내는 f가 있음<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/752aa39b-b810-4c56-a2bc-bb27b9d5bad9)<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b9e2f3ae-a428-41f1-9545-618293cf45e4)<br/>
논리적인 메모리에 있는 페이지들은 연속적이지만, 물리적인 메모리의 페이지들은 아님<br/>
OS는 각 프로세스의 페이지 테이블을 관리해야 함<br/>

Paging Calculate<br/>
-
Internal fragmentation이 발생<br/>
1. page size = 2048 bytes<br/>
2. process size = 72766 bytes 라고 가정<br/>
35pages + 1086 bytes 라고 볼 수 있음<br/>
1086byes 또한 한 페이지 안에 적혀있기 때문에, 2048-1086 = 962bytes (Internal fragmentation 발생)<br/>
Worst case의 fragmentation = 1frame - 1byte<br/>
Average case fragmentation = 1/2 frame size<br/>

페이지의 크기를 작게 만들면 fragmentation도 줄어들지 않을까??<br/>
1. 페이지 테이블의 엔트리 수 증가<br/>
2. 일반적으로 페이지 크기는 증가하는 추세<br/>
3. 가장 인기있는 크기는 4KB 와 8KB<br/>
4. 페이지 테이블에는 frame 값 이외에도 추가 정보를 저장할 공간 필요<br/>

Free Frames<br/>
-
Frame table - 각 프레임이 어떤 프로세스의 어떤 페이지에 할당되었는지에 대한 정보<br/>
Free-frame list - 비어 있는 공간을 알 수 있음<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7593796e-aa4a-494f-83b8-7f4cdf619309)<br/>

Page table 구현<br/>
-
프로세스는 main memory에 고유한 page table을 가지고 있음<br/>
1. Page-table base register(PTBR) - 페이지 테이블의 시작 주소<br/>
2. Page-table length register(PTLR) - 페이지 테이블의 길이<br/>
3. Page table을 메모리에 가지고 있기 때문에, 데이터에 접근하려면 총 2번의 memory accesses가 발생(page table참조 + 참조하여 얻은 물리적 주소를 사용하여 실제 데이터나 명령어에 접근하여 읽음)<br/>
-> CPU 입장에서 2번의 메모리 조회는 비싼 비용인데 가까운 곳에 cache처럼 page table을 둔다면 비용이 적지 않을까??<br/>
   1. Translation look-aside buffers(associative memory or content addressable memory)<br/>
      1. 검색이 가능한 저장 공간<br/>
      2. 실행 속도가 빠르다. page number을 주면 바로 frame 숫자가 나오는 느낌?<br/>

Translation look-aside buffer<br/>
-
빠른 저장 공간(cache 랑은 다름)<br/>
이 저장 공간을 들여다 보는 것은 비용이 들어가지 않음 <br/>
1. (병렬로 모든 엔트리를 검색하기에 빠르게 찾을 수 있음) <br/>
2. TLB look up은 프로세서의 명령어 처리 과정에 통합되어 있 <br/>

Context switch를 하게 되면 현재 table은 무의미하게 될 수 있으므로, Address-space identifiers를 통해서 어떤 프로세스인지 알 수 있게 함 <br/>
어떤 CPU는 instruction TLB와 data TLB를 별도로 가지기도 하며, TLB는 계층 구조를 가지기도 함 <br/>
TLB는 small size <br/>
TLB가 없으면 페이지 테이블을 조회하고, 조회한 결과를 TLB로 가져옴<br/>
TLB 값들은 교체될 수 있는데, 제거할 수 없는 entry가 존재함(일반적으로 주요한 커널 코드의 엔트리)<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/2d3b0511-6c95-4f9c-9beb-434c3d5d0822)<br/>

Effective Access Time<br/>
-
TLB에 원하는 데이터가 있을 확률 - hit ratio<br/>
TLB버퍼에 있는 페이지를 frame으로 찾는 시간은 거의 안 안듦<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/a9335dc7-fefb-47da-ad7e-2d3a64e22212)<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6db90e30-5395-4b8d-9e1c-cd080d9df7d4)<br/>

hit ratio가 높으면 거의 메모리를 1번 조회하는 효과<br/>

Memory Protection<br/>
-
Page table에는 entry에 frame number 말고도 몇 가지 정보를 저장할 수 있음<br/>
1. Protection bit - 읽기 전용인지, 읽고 쓸 수 있는 영역인지, 실행할 수 있는지 등<br/>
2. Valid-Invalid bit<br/>
   1. 유효한 entry는 논리적인 주소에 있는 page가 frame에 매칭되는 경우<br/>
   2. 유효하지 않으면 page가 논리적인 주소에 없는 경우<br/>
   3. 유효한지 아닌지는 page-table length register로도 알 수 있음 <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/52ed55aa-d69b-47f9-8f25-909bf95f69e2)<br/>
주소 공간 14bit = 16384<br/>
페이지 크기 2KB = 2^11 = 2048bytes<br/>
페이지 수 = 16384 / 2048 = 8 이므로 8개의 페이지로 나누어짐<br/>
주어진 프로그램이 0부터 10468 주소만 사용하는 경우라면 페이지 4번까지만 유효하므로, 페이지 5~7번은 invalid해야 정상<br/>
이미지에서 valid하다고 나오는 오류는 Internal fragmentation of paging<br/>

Shared Pages<br/>
- 
Shared code<br/>
1. 하나의 copy된 읽기 전용 코드를 여러 프로세스 사이에서 공유<br/>
2. 프로세스 공간 공유를 통해서 여러 스레드가 동일한 프로세스 공간을 공유하는 것과 유사<br/>
3. 읽기/쓰기가 가능한 페이지의 공유가 허용되는 경우, 프로세스간 통신에 유용함<br/>
  일부 OS는 공유 페이지를 통해서 공유 메모리 구현<br/>

Private code <br/>
1. 별도의 코드와 데이터를 가짐(공유가 아님)<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/20a14dbc-c9d3-432f-9ff1-f702ae06c8e1)<br/>
개별적으로 사용한다고 process는 생각하지만, 물리적인 메모리에서는 결국 공유하고 있는 형태<br/>

논리적인 주소 공간 32bit<br/>
페이지 크기 4KB 라고 가정<br/>
page table은 2^32 / 2^12 = 2^20 개의 entry를 가짐<br/>
each entry가 만약 4bytes면 page table의 크기는 4bytes * 2^20 = 4MB<br/>
-> Page table이 너무 커서 handling하기 어려움<br/>

Hierarchical Paging<br/>
-
offset을 제외한 page number의 크기를 다시 자르는 것<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/4d02e9bf-7d81-465d-a4d7-bb614eea292d)<br/>
p1은 outer page table, p2는 inner page table<br/>

왜 10bit로 나눠?? -> 각 테이블의 크기가 4KB로 동일하게 나눠 떨어져서<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6d73c4d2-0ae2-4c88-a217-6bbb0273542d)<br/>

방의 크기가 4bytes라면 table 크기는 4bytes*2^10 = 4KB<br/>
작은 사이즈의 페이지 테이블로 나눠, 계층적 구조를 만듦<br/>
64bit는 너무 커서 계층 구조로 사용하지 않음<br/>

Hahsed Page Tables<br/>
-
32bit 이상이면 크니까 Hashed Page 사용하고, 32bit보다 작으면 계층구조 사용<br/>
entry에는 page number, frame, pointer가 존재<br/>
open hashing - 해시 테이블에서 충돌을 처리하기 위해 각 버킷이 여러 엔트리 저장<br/>
clustered page tables - 하나의 노드에 여러 개의 페이지 테이블 엔트리를 저장 <br/>

Inverted Page Tables<br/>
-
1. Physical 한 frame table은 시스템에 하나 존재함<br/>
2. 프로세스마다 페이지 테이블을 가지지 말고, 물리적 페이지를 직접 관리하는게 어떤가?<br/>
3. 프로세스가 사용하는 logical address가 있는데, 그걸 physical address로 부터 찾아냄<br/>
4. 페이지 테이블을 저장하는 메모리는 줄어들지만, 검색 시간이 증가<br/>
5. 검색 시간을 줄이기 위해 추가적인 hash table 사용 가능<br/>
6. 공유 메모리 공유는 불가능<br/>
7. Table은 시스템에 한 개만 있으면 되므로, 메모리 공간 절약<br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/180c23c9-607d-43c3-8a1d-d52a3c4c7cf3)<br/>

Swapping<br/>
-
메모리가 부족하면 그 중 하나의 프로세스를 통째로 바깥으로 내 보내는 방식<br/>
1. 디스크에다가 옮겨 놓음(backing store)<br/>
2. Roll out , Roll in - 바깥에 내보냈던 것을 다시 불러들임<br/>
3. swap time에서 가장 큰 부분은 transfer time(전송되는 메모리 양에 비례)<br/>
4. 새로 들어온 프로세스는 CPU를 받을 준비가 되었을 테니까 ready queue를 유지<br/>
5. Standard swapping - 프로세스 전체 swap<br/>
6. Swapping = Standard swapping<br/>
7. Paging = swapping with paging (페이지 단위로 스와핑)<br/>

Swap을 하면 나갔다가 다시 돌아왔을 경우, 같은 공간으로 들어오지 않을 수 있음<br/>
1. 일반적으로 동일할 필요는 없지만, I/O 버퍼와 같이 주소 바인딩에 따라 요구될 수 있음<br/>
2. 일반적으로 제한<br/>
3. 피치못할 상황이 발생하면 실행<br/>
4. 상황이 복구되면 다시 복구<br/>

Schematic View of Swapping<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/fd8abbea-dca1-4a09-bf4d-4bf9a269dbd6)<br/>

Context Switch Time including Swapping<br/>
Context switch time은 매우 높음
100MB process를 swapping 하는데, transfer rate 가 50MB/sec이면 2초가 걸리고, 전체 context switch time은 4초가 걸린다.
스와핑에 필요한 실제 메모리 용량을 OS에 알려주면 불필요한 스와핑을 줄일 수 있음 why?? -> 메모리 관리를 효율적으로 함

제약사항
Pending I/O(대기 중인 I/O)
1. 대기 중인 I/O 작업이 있는 경우, 해당 프로세스를 swap out 할 수 없음
2. I/O작업이 완료 되면 해당 데이터가 다른 프로세스로 잘못 전달될 수 있음

Double Buffering
1. 모든 I/O작업을 커널 공간으로 전송한 후, 다시 I/O 디바이스로 전송
2. 정확성 보장하지만, 추가적인 오버헤드 발생

현대의 swapping - 메모리가 극도로 부족한 경우에만 swapping 수행

Swapping on Mobile Systems
-
Swapping 을 사용하지 않음
1. 모바일은 flash memory 기반이라서 저장 공간이 작
2. Write cycle에 제한이 있음(SSD는 overwrite 불가능, 별도의 erase cycle필)
3. 낮은 처리량

IOS 같은 경우에는 자발적으로 할당된 메모리를 놓도록 요청함
1. IOS는 app에 할당된 메모리를 자발적으로 반환하도록 요청
2. 읽기 전용 데이터는 필요시 다시 로드할 수 있으므로 먼저 제거
3. 메모리를 반환하지 않으면 종료

Android
1. free memory가 부족할 경우 app 종료
2. 종료 전에 app 상태를 flash memory에 저장하여, 빠른 재시작 가능하게 함

공통적으로 paging을 지원하고, memory compression을 사용한다.

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/cb4cf360-5da9-4c4a-badb-e92a35d5ac3c)

page table은 main memory에 있고, page table의 entry 논리적인 주소이므로 연속적이여야 함















