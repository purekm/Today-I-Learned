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
Load time - 메모리 위치가 알려지지 않은 경우 relocateable code는 상대적인 주소이기 때문에 loading되는 순간 address에 대한 계산을 통해 실제 address를 알 수 있다.<br/>
Execution time - 프로세스가 실행 중 다른 메모리 위치로 이동할 수 있는 경우에 실행시간에 binding이 이루어진다. Runtime 전까지 binding이 지연될 수 있고 hardware의 지원이 필요하다.<br/>
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

Dynamic loading과 달리 dynamic linking과 shared libraries는 OS의 도움이 필요



