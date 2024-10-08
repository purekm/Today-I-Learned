
---

# Chapter 2 - Overview

## Objectives
1. 운영 체제가 제공하는 서비스 설명
2. 운영 체제 서비스를 제공하기 위해 시스템 호출이 사용되는 방법
3. 단일형, 계층형, 마이크로 커널, 모듈형, 하이브리드 전략을 비교
4. 운영 체제를 부팅하는 과정 설명
5. 운영 체제 성능 모니터링 도구 적용
6. 커널과 상호 작용하기 위한 커널 모듈 설계 및 구현

## 운영체제가 제공하는 서비스
1. **User Interface**: CLI, GUI, 터치스크린, 배치
2. **Program execution**: 메모리로 프로그램을 로드하고 실행시키기
3. **I/O operations**: 실행 중인 프로그램이 필요한 I/O 제공
4. **File-system manipulation**: 파일과 디렉토리를 읽고 쓰기, 권한 관리
5. **Communication**: 프로세스 간 정보 교환, 네트워크를 통한 컴퓨터 간 정보 교환
6. **Error detection**: 발생한 오류를 지속적으로 인지하고 처리
7. **Resource allocation**: 여러 사용자가 동시에 여러 작업을 실행할 때 자원을 할당
8. **Logging**: 어떤 사용자가 얼마나 많은 자원을 사용했는지 추적
9. **Protection and security**: 시스템 자원에 대한 접근 통제 및 외부로부터 시스템 보호

## System call
시스템 호출은 운영 체제가 제공하는 서비스에 대한 프로그래밍 인터페이스로 API를 통해 접근함
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/36e2ff18-658c-4f8a-9771-bee5f3f44cc6)

각 시스템 호출에는 연결된 번호와 그에 따른 테이블이 존재함. 시스템 호출을 호출하고, 시스템 호출의 상태 및 반환 값을 반환함.

인터럽트 호출은 현재 레지스터에 정보를 전부 저장하고 반환한 후, 호출이 끝나면 복구함.

시스템 호출에는 단순히 원하는 시스템 호출의 식별 이상으로 많은 정보가 필요함. 매개변수를 OS에 전달하는 데 사용되는 방법 3가지가 있음:
1. **레지스터에 파라미터 전달**
2. **메모리 블록 또는 테이블에 파라미터를 저장하고 블록의 주소를 레지스터에 저장**
3. **파라미터를 프로그램에 의해 스택에 놓고, 운영 체제에 의해 스택에서 팝**

레지스터에 배열은 저장할 수 없기 때문에, 배열을 저장해야 할 경우 주소를 저장함.

## Linker and Loader
링커와 로더는 컴파일된 프로그램을 실행 가능한 형태로 준비하는 역할을 함.

### Linker
1. 소스 코드는 개별적으로 컴파일되어 객체 파일이 됨.
2. 링커는 이 객체 파일들을 하나의 바이너리 실행 파일로 결합함.
3. 링커는 라이브러리를 가져와 프로그램에 포함시킴.

### Loader
1. 프로그램은 바이너리 실행 파일 형태로 보조 기억 장치에 저장됨.
2. 이 파일을 메모리에 로드하여 실행 준비를 함.

현대 범용 시스템에서는 라이브러리를 실행 파일에 포함시키지 않고, 필요할 때 동적으로 링크된 라이브러리를 로드함.

## 운영 체제 설계 전략
1. **단일형 (Monolithic)**: 운영 체제의 모든 기능이 커널 공간에서 실행되는 구조
   - 장점: 모든 기능이 커널에서 실행되므로 시스템 호출 간 오버헤드가 적고, 간단한 구현
   - 단점: 커널이 크고 복잡해질수록 디버깅과 유지 보수가 어려움

2. **계층형 (Layered Approach)**: 운영 체제를 계층으로 나누어 각 계층이 바로 아래 계층의 기능만을 사용하는 구조
   - 장점: 모듈화가 되어 각 계층이 독립적으로 설계되고 구현 가능하여 유지보수가 편리하고, 오류가 다른 계층으로 전파되는 것을 막을 수 있음
   - 단점: 계층 간의 호출이 많아질수록 성능이 저하될 수 있고, 설계가 복잡함

3. **마이크로 커널 (Microkernel)**: 최소한의 기능을 커널에 포함하고 나머지 기능을 사용자 공간에서 실행하는 구조
   - 장점: 확장성이 좋고, 사용자 공간에서 실행되는 서비스 간의 격리가 이루어져 안정성과 보안성이 높아짐
   - 단점: 커널과 사용자 공간 간의 빈번한 통신으로 오버헤드가 발생할 수 있고, 구현이 복잡함

4. **모듈형 (Modular)**: 커널을 여러 모듈로 나누어 필요한 모듈만 동적으로 로드하여 사용하는 구조
   - 장점: 필요에 따라 모듈을 추가하거나 제거할 수 있어 유연하고, 각 모듈이 독립적으로 개발되어 유지보수가 용이함
   - 단점: 초기에 어떤 모듈이 필요한지 설계하기 복잡하고, 모듈 간의 인터페이스를 통해 호출이 이루어지므로 약간의 성능 저하가 있을 수 있음

5. **하이브리드 (Hybrid)**: 위의 구조들의 장점을 결합한 구조
   - 장점: 최적화된 성능 제공
   - 단점: 설계가 복잡함

## System boot
1. 전원이 켜지면 실행이 고정된 메모리 위치에서 시작됨.
2. 운영 체제를 하드웨어에서 사용할 수 있도록 bootstrap loader에 의해 수행됨.
3. Bootstrap loader는 운영 체제 커널을 찾고, 이를 메모리에 로드하여 실행을 시작함.
4. 시스템이 실행되기 시작하면 커널은 하드웨어 초기화 및 자원 할당을 수행하고, 기본 프로세스 및 데몬을 시작함.

## Why Applications are Operating System Specific
- 애플리케이션은 특정 운영 체제에서만 실행될 수 있는 경우가 많음. 각 운영 체제는 고유한 시스템 호출과 파일 형식을 제공하기 때문에, 다른 운영 체제에서 동일한 애플리케이션을 실행하려면 별도로 컴파일해야 함. 또한, 인터프리터를 사용하거나 가상 머신을 통해 다중 운영 체제에서 실행 가능한 애플리케이션을 작성할 수 있음.

## Debug
디버깅은 시스템에서 발생하는 오류를 찾아 수정하는 과정으로, OS의 안정성과 성능을 유지하는 데 중요한 역할을 함.

### 로그 파일
오류 정보를 포함한 파일.

### Core Dump
애플리케이션 오류가 발생하면 프로세스의 메모리 상태를 캡처한 코어 덤프 파일 생성.

### Crash Dump
운영 체제 자체의 오류가 발생하면 커널 메모리를 캡처한 크래시 덤프 파일 생성.

### 성능 튜닝
시스템 성능 최적화를 위해 병목 현상을 제거함. `top` 프로그램이나 Windows Task Manager와 같은 도구를 사용하여 시스템의 성능을 모니터링하고 분석할 수 있음.

### Tracing and Debugging Tools
- 시스템 콜 추적 및 디버깅을 위한 도구로는 `strace`, `gdb`, `perf`, `tcpdump` 등이 있음. 이러한 도구들은 시스템 콜을 추적하거나 네트워크 패킷을 수집하여 시스템의 동작을 분석하고, 오류를 수정하는 데 유용함.

---

## 실시간 운영체제 (Real-Time Operating Systems, RTOS)

### 정의
실시간 운영체제(RTOS)는 응답 시간이 중요한 시스템에서 사용되는 운영체제로, 정해진 시간 내에 작업을 처리해야 하는 요구사항을 충족시키기 위해 설계됨. 예측 가능한 응답 시간이 가장 중요한 요소임.

### 주요 특징
1. **확정성(Determinism)**: RTOS는 일정한 시간 내에 모든 작업이 완료될 것임을 보장함. 이는 시스템이 일정한 주기나 이벤트에 대해 항상 일정한 시간 내에 응답해야 하는 환경에서 필수적임.
   
2. **우선순위 기반 스케줄링(Priority-Based Scheduling)**: RTOS는 작업의 우선순위에 따라 스케줄링을 수행함. 높은 우선순위를 가진 작업은 즉시 처리되며, 이를 통해 중요한 작업이 지연 없이 실행될 수 있음.

3. **미세한 시간 제어(Fine-Grained Timing Control)**: RTOS는 매우 짧은 시간 단위로 작업을 제어할 수 있음. 이는 센서나 제어 시스템과 같은 환경에서 필요한 빠르고 정밀한 시간 제어를 가능하게 함.

### 응용 분야
- **임베디드 시스템(Embedded Systems)**: 가전제품, 자동차, 의료 기기 등에서 사용됨. 예를 들어, 자동차의 엔진 제어 시스템이나 항공기 내의 제어 시스템 등에서 실시간 운영체제가 필요함.
  
- **산업 자동화(Industrial Automation)**: 공장 자동화 시스템, 로봇 제어 시스템 등에서 사용됨. 이러한 시스템은 일정한 주기 내에 작업을 완료해야 하므로 RTOS가 적합함.
  
- **통신 시스템(Communication Systems)**: 네트워크 장비나 이동통신 시스템에서 실시간 데이터를 처리하기 위해 RTOS가 사용됨.

### 일반 운영체제와의 차이점
- **일반 운영체제**는 다양한 작업을 처리할 수 있도록 설계되어 있으며, 작업의 처리 시간에 유연성이 있음. 예를 들어, 데스크탑 운영체제에서는 여러 응용 프로그램이 동시에 실행되더라도 특정 작업이 지연되는 것을 큰 문제로 보지 않음.
  
- **RTOS**는 특정 작업이 정해진 시간 내에 반드시 완료되어야 하는 경우에 사용되며, 작업의 시간 제약을 엄격하게 준수함.

### 예시
- **FreeRTOS**: 오픈 소스 실시간 운영체제로, 임베디드 시스템에서 널리 사용됨.
- **VxWorks**: 상용 실시간 운영체제로, 항공기와 같은 고신뢰성 시스템에서 사용됨.
- **QNX**: 자동차 인포테인먼트 시스템과 같은 분야에서 사용되는 RTOS로, 높은 신뢰성과 확정성을 제공함.
