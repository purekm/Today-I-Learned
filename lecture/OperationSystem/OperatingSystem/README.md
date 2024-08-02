

---

# Chapter 1 - Overview

## 컴퓨터 시스템의 구조
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/4dd612a8-5841-45e5-bacd-1785d49c2067)

OS는 User가 활용하기 쉽도록 자원 할당과 프로그램을 제어해줍니다.  
OS는 시스템의 효율성과 반응성을 높이기 위해 interrupt를 통해 작동합니다.  
Interrupt는 CPU가 현재 수행 중인 작업을 일시적으로 중단하고, 즉시 다른 작업을 처리하도록 하는 메커니즘입니다.  

## Interrupt 발생 과정
1. 인터럽트가 발생하면, 현재 실행 중이던 명령어의 주소를 저장하고 시스템은 인터럽트 벡터를 통해 적절한 인터럽트 서비스 루틴(ISR)으로 제어를 넘깁니다.
2. ISR이 실행을 완료하면, CPU는 저장된 작업 상태를 복원합니다(PC, register 정보).
3. 이후 CPU는 중단되었던 원래 작업을 재개합니다.

Interrupt는 Polled, Vectored 유형이 존재합니다:
- **Polled interrupt system**: CPU가 주기적으로 각 장치를 확인하여 인터럽트가 발생했는지 검사
- **Vectored interrupt system**: 인터럽트 벡터를 사용하여 특정 인터럽트 서비스 루틴을 바로 호출

## I/O 발생 시 인터럽트 처리 과정
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/d1a8f033-27f5-47e1-8964-2982238760d6)

## Storage Structure
- **Main memory**: Random access, volatile (DRAM)
- **Hard Disk Drives (HDD)**: Non-volatile storage
- **Non-volatile memory (NVM) devices**: 하드디스크보다 빠르고, 비휘발성인 다양한 장치들

Storage Hierarchy는 속도, 비용, 휘발성 여부로 계층이 정해집니다.  
**Caching**: 정보를 복제해서 빠르게 접근할 수 있도록 하는 storage system입니다.  
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/aae2e88d-4515-4fd7-8643-bddf17231cc0)

## 현대 컴퓨터 구조
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/74fb5cb6-1189-4761-bff5-22f6132bedde)

**Direct Memory Access Structure (DMA)**: 블록 단위의 데이터를 CPU의 관여 없이 메모리에 한번에 옮기고 난 이후에 CPU에게 후 보고 하는 방식으로, interrupt는 block 단위로 발생합니다.

대부분의 시스템은 하나의 목적을 가진 프로세서를 사용하지만, 요즘엔 Multiprocessor system이 많아지고 있습니다.  
전문화된 processor가 있으면 Asymmetric 방식, 다 같은 동작을 한다면 Symmetric 방식입니다.  
모든 CPU는 각자의 메모리를 가지고 있는데, 다른 메모리 영역에 접근할 때는 다른 CPU를 통해서 접근해야 합니다.  
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/d470412f-887d-4040-9ccd-6ea1afe5be6a)

## OS 동작
Bootstrap 프로그램은 시스템이 켜질 때 실행되는 간단한 코드로, 시스템을 초기화하고 운영 체제의 핵심 부분인 커널을 메모리에 로드합니다.  
커널은 운영 체제의 핵심 부분으로, 하드웨어와 소프트웨어 간의 인터페이스 역할을 합니다.  
커널이 로드된 후, 시스템 데몬(커널 외부에서 제공되는 서비스들로, 백그라운드에서 실행되며 시스템의 다양한 기능 제공)들이 시작됩니다.  

커널은 interrupt 기반으로 동작을 하는데, Hardware interrupt와 Software interrupt로 나뉩니다:
- **Hardware interrupt**: 하드웨어 장치(키보드, 마우스)에서 발생하는 신호
- **Software interrupt**: 프로그램에서 오류가 발생하거나, OS의 서비스를 요청할 때 발생

우리 OS는 시 분할 시스템이지만, 멀티 프로그래밍 방식도 사용합니다:
- **멀티 프로그래밍**: 시스템의 효율성을 높이기 위해 여러 작업을 메모리에 로드하여 CPU가 항상 작업을 실행하도록 합니다.
- **시분할**: CPU가 여러 사용자나 작업 사이에서 빠르게 전환하여 사용자가 interactive하게 시스템을 사용할 수 있도록 합니다.

## Dual-Mode와 Multimode Operation
OS는 User mode와 Kernel 모드를 운영하여 자신과 다른 시스템 구성 요소를 보호할 수 있게 합니다.  
User mode에서 Kernel 모드로 넘어가기 위해서는 system call을 호출합니다.  
System call을 호출하면, 트랩이 발생하여 mode bit가 0이 되어 kernel mode로 전환됩니다.  
Kernel mode에서도 system call이 실행되면 다시 사용자 모드로 복귀합니다.  
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7435039b-0cf9-4dab-a289-2e4ba18bb8ae)

## Process와 Thread
하나의 process에는 여러 개의 실행 형태(Thread)가 있을 수 있습니다:
- **Process**: 집이라고 생각하고
- **Thread**: 구성원이라고 생각하면 좋습니다.
모든 process는 최소한 하나의 Thread를 가지며, Thread는 서로 무언가 공유하는 부분을 가집니다.


## 운영체제의 보안과 보호 기능

운영체제는 시스템의 안정성과 보안을 유지하기 위해 다양한 보호 및 보안 메커니즘을 제공합니다.

### 보호 기능 (Protection)
- **보호 기능**은 프로세스나 사용자가 시스템 자원에 접근하는 것을 제어하는 메커니즘입니다.
- 이는 시스템의 무결성을 유지하고, 각 사용자와 프로세스가 허가된 자원만 접근할 수 있도록 합니다.

### 보안 (Security)
- **보안**은 시스템을 내부 및 외부의 다양한 공격으로부터 방어하는 메커니즘입니다.
- 이는 서비스 거부 공격(DoS), 웜(Worms), 바이러스(Viruses), 신원 도용(Identity Theft) 등과 같은 위협에 대응합니다.
- 시스템은 각 사용자에게 고유한 사용자 ID(User ID)와 그룹 ID(Group ID)를 부여하여 접근 권한을 관리합니다.
- **권한 상승(Privilege Escalation)**은 사용자가 특정 작업을 수행하기 위해 자신의 권한을 일시적으로 더 높은 권한으로 변경하는 메커니즘입니다.

---

## 가상화와 분산 시스템

### 가상화 (Virtualization)
- **가상화**는 하나의 물리적 컴퓨터에서 여러 개의 운영체제를 동시에 실행할 수 있게 해주는 기술입니다.
- 이는 가상 머신 관리자(Virtual Machine Manager, VMM)를 통해 이루어지며, 다양한 운영체제 환경에서 응용 프로그램을 개발하거나 테스트할 때 유용합니다.
- 가상화는 데이터 센터에서 자원의 효율적인 활용을 가능하게 하며, 다양한 OS를 동일한 하드웨어에서 실행할 수 있게 해줍니다.

### 분산 시스템 (Distributed Systems)
- **분산 시스템**은 네트워크로 연결된 여러 독립적인 컴퓨터 시스템들이 협력하여 작업을 수행하는 시스템입니다.
- 이러한 시스템은 고가용성(high availability)을 제공하며, 클러스터링 기술을 통해 서버가 고장 나더라도 서비스를 지속할 수 있습니다.
- 분산 시스템은 다양한 물리적 위치에 있는 컴퓨터들이 네트워크를 통해 상호작용하면서 하나의 시스템처럼 동작합니다.

---