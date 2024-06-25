Chapter 1 - Overview <br/>

컴퓨터 시스템의 구조 <br/>

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/4dd612a8-5841-45e5-bacd-1785d49c2067)<br/>
OS는 User가 활용하기 쉽도록 자원 할당과 프로그램을 제어해준다. <br/>

OS는 시스템의 효율성과 반응성을 높이기 위해 interrupt를 통해 작동한다. <br/>
Interrupt는 CPU가 현재 수행중인 작업을 일시적으로 중단하고, 즉시 다른 작업을 처리하도록 하는 메커니즘이다. <br/>


Interrupt 발생 과정 <br/>
-
인터럽트가 발생하면, 현재 실행 중이던 명령어의 주소를 저장하고 시스템은 인터럽트 벡터를 통해 적절한 인터럽트 서비스 루틴으로 제어를 넘긴다. (인터럽트 벡터는 모든 서비스 루틴의 주소를 저장하고있음) <br/>
이후 ISR이 실행을 완료하면, CPU는 저장된 작업 상태를 복원한다.(PC,register 정보)<br/>
이후 CPU는 중단되었던 원래 작업을 재개한다.<br/>

Interrupt는 Polled , Vectored 유형이 존재한다.<br/>
Polled interrupt system - CPU가 주기적으로 각 장치를 확인하여 인터럽트가 발생했는지 검사 <br/>
Vectored interrupt system - 인터럽트 벡터를 사용하여 특정 인터럽트 서비스 루틴을 바로 호출 <br/>

I/O 발생시 인터럽트 처리 과정<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/d1a8f033-27f5-47e1-8964-2982238760d6)<br/>

Storage Structure <br/>
-
Main memory - Random access , volatile <br/>
Dynamic Random-access Memory(DRAM) 이라고 부른다.<br/>

Hard Disk Drives(HDD) - non volatile storage <br/>
Non-volatile memory (NVM) devices - 하드디스크 보단 빠르고, 비휘발성인 다양한 장치들 <br/>

Storage Hierarchy 에서 요소들은 속도, 비용, 휘발성 여부로 계층이 정해진다. <br/>
Caching - 정보를 복제해서 빠르게 접근할 수 있도록 하는 storage system <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/aae2e88d-4515-4fd7-8643-bddf17231cc0)<br/>

현대 컴퓨터 구조 <br/>
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/74fb5cb6-1189-4761-bff5-22f6132bedde)<br/>
Direct Memory Access Structure(DMA) - 블록 단위의 데이터를 CPU의 관여 없이 메모리에 한번에 옮기고 난 이후에 CPU에게 후 보고 하는 방식으로 interrupt는 block 단위로 발생 <br/>

대부분의 시스템은 하나의 목적을 가진 프로세서를 사용하지만, 요즘엔 Multiprocessor system이 많아지고 있다. <br/>
전문화 된 processor가 있으면 Asymmetric 방식, 다 같은 동작을 한다면 Symmetric 방식이다. <br/>

모든 CPU는 각자의 메모리를 가지고 있는데, 다른 메모리 영역에 접근할 때는 다른 CPU를 통해서 접근해야 한다.<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/d470412f-887d-4040-9ccd-6ea1afe5be6a)<br/>

OS 동작 <br/>
-

Bootstrap 프로그램은 시스템이 켜질 때 실행되는 간단한  코드로, 시스템을 초기화하고 운영 체제의 핵심 부분인 커널을 메모리에 로드한다. <br/>
커널은 운영 체제의 핵심 부분으로, 하드웨어와 소프트웨어 간의 인터페이스 역할을 한다.<br/>
커널이 로드된 후, 시스템 데몬(커널 외부에서 제공되는 서비스들로, 백그라운드에서 실행되며 시스템의 다양한 기능 제공)들이 시작한다. <br/>
<br/>
커널은 interrupt 기반으로 동작을 하는데, Hardware interrupt와 Software interrupt로 나뉜다. <br/>
Hardware interrupt - 하드웨어 장치(키보드, 마우스)에서 발생하는 신호 <br/>
Software interrupt - 프로그램에서 오류가 발생하거나, OS의 서비스를 요청할 때 발생 <br/>

우리 OS는 시 분할 시스템이지만, 멀티 프로그래밍 방식도 사용한다. <br/>
멀티 프로그래밍은 시스템의 효율성을 높이기 위해 여러 작업을 메모리에 로드하여 CPU가 항상 작업을 실행하도록 한다.<br/>
시분할은 CPU가 여러 사용자나 작업 사이에서 빠르게 전환하여 사용자가 interactive하게 시스템을 사용할 수 있도록 한다.<br/>

OS는 User mode와 Kernel모드를 운영하여 자신과 다른 시스템 구성 요소를 보호할 수 있게 한다.<br/>
User mode에서 Kernel모드로 넘어가기 위해서는 system call을 호출한다. <br/>
System call을 호출하면, 트랩이 발생하여 mode bit가 0이 되어 kernel mode로 전환된다.<br/>
Kernel mode에서도 system call이 실행되면 다시 사용자모드로 복귀한다. <br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7435039b-0cf9-4dab-a289-2e4ba18bb8ae)<br/>

하나의 process에는 여러 개의 실행 형태(Thread)가 있을 수 있다. <br/>
Process를 집이라고 생각하고, Thread를 구성원이라고 생각하면 좋다. <br/>
모든 process는 최소한 하나의 Thread를 가진다.<br/>
Process와 Thread의 차이점으로는, Thread는 서로 무언가 공유하는 부분을 가진다.<br/>








