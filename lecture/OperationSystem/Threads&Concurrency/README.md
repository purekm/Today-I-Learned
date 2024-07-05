Chapter4
Objectives
1. 스레드의 기본 구성 요소 이해 및 프로세스와 비교
2. 멀티 스레딩의 장점과 구현할 때 challenge
3. 스레딩에 대한 다양한 접근 방법
4. 리눅스 운영 체제가 스레드를 어떻게 나타내는지 설명

요즘 applications 들은 대부분 multithreaded 방식
application 내에서 여러 작업들은 별도의 스레드로 구현될 수 있다.
예를 들어 화면 업데이트, 데이터 가져오기, 맞춤법 검사, 네트워크 요청 처리 등
프로세스 생성은 무거운 작업인 반면, 스레드 생성은 가벼운 작업
커널은 대부분 multithreaded로 작동

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7eb50ef9-5c24-4dc8-bdf6-b84a9498e564)
single-thread 는 그냥 프로세스라고 생각해도 무방한 것 같다.
multithreaded 에서는 독립적인 register, stack, PC를 가지면서 code, data files 를 공유한다.

Multithread
-
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7006a689-d6bd-4443-9613-196e3c3ff8af)
멀티 스레드 서버는 클라이언트 요청을 처리하기 위해 여러 스레드를 사용한다.
이런 접근 방식은 서버의 응답성을 향상시키고, 여러 클라이언트의 요청을 동시에 처리할 수 있게 한다.

Multithreading 장점
1. Responssiveness(응답성) - 프로세스의 일부가 블록되어도 계속 실행될 수 있어서, 특히 사용자 인터페이스에 중요
2. Resource Sharing(자원 공유) - 스레드는 프로세스의 자원을 공유하므로 공유 메모리 or 메시지보다 쉽게 자원 공유 가능
3. Economy(경제성) - 스레드 생성이 프로세스 생성보다 저렴하고, 스레드 전환이 context switch보다 오버헤드가 적음
4. Scalability(확장성) - 프로세스가 멀티코어 구조의 장점을 활용할 수 있음

Parallelism(병렬) - 시스템이 동시에 둘 이상의 작업을 수행 
Concurrency(병행) - 둘 이상의 작업이 진행 중 (단일 프로세서/코어의 경우)

Amdahl's Law - application의 병렬 및 직렬 컴포넌트를 고려한 성능향상 평가 

User Threads and Kerenel Threads
-
User 와 Kernel 관계 (Many to One, One to One, One to Many)
Many to One 
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7ddb2378-f3e7-4dce-8584-5abf111f9c5f)
사용자 프로세스에 상응하는 커널 스레드가 하나만 있음
장점으로 원하는 만큼 사용자 스레드를 생성할 수 있음

One to One (현대 OS)
스레드가 블로킹되면 다른 스레드를 실행할 수 있고, 여러 개의 스레드를 다중 코어에 매핑할 수 있음
하지만 사용자 스레드를 무한정 생성할 수 없음

Many to Many
이론상 사용자 스레드 맘대로 생성가능하고, 병렬 실행도 가능하지만 구현이 어려움

Two-level
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1700d5d0-6010-4463-9513-0cd5461d14ea)
두 관계가 동시에 실행되는 모델도 존재

Thread Libraries - 프로그래머에게 스레드를 생성하고 관리할 수 있는 API 제공
Asynchronous threading(비동기 스레딩) - 부모와 자식 스레드가 독립적으로 병행 실행
Synchronous threading(동기 스레딩) - 부모 스레드는 자식 스레드가 종료될 때 까지 기다림

Thread Pool
스레드를 필요할 때 사용할 수 있도록 만들어 놓는 것
장점
1. 기존 스레드를 재사용하여 새로운 스레드를 생성하는 것보다 빠르게 요청처리 가능
2. application의 스레드 수를 풀의 크기로 제한 가능
3. 작업을 수행하는 것과 작업을 생성하는 것을 분리하여 다양한 실행 전략을 사용할 수 있음

Fork-Join Parallelism - 여러 스레드를 fork하여 생성하고, 완료된 후에는 join하여 결과를 결합하는 방식
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/387fa10d-facc-4244-9b9a-6f95f6af9dd5)

Signal Handling
-
Signal - 특정 이벤트가 발생했음을 프로세스에 알리는 데 사용
default는 signal을 받았을 때 dead(종료)
Signal handler - signal 처리
Signal이 왔을 때 코드를 실행시키고 싶으면 Handler를 사용

Multi-Thread에 signal이 온 경우
Signal을 허용할 수 있는 thread 중 아무나한테 signal을 보냄 (오류난 thread 죽이는 경우)
모든 thread에게 보냄 (프로세스를 끝내는 경우)
어떤 thread에게 보냄 (가능한 thread 중 아무나 실행)
특정 thread에게 보냄

Thread Cancellation
-
Thread Cancellation - 스레드가 완료되기 전에 종료되는 것을 의미
Target Thread - 취소될 스레드
Thread Cancellation 에는 두 가지 일반적인 방식이 존재
1. Asynchronous cancellation(비동기 취소) - 대상 스레드를 즉시 종료
   할당된 자원을 모두 free하지 못할 수 있음
2. Deferred cancellation(지연 취소) - 대상 스레드가 주기적으로 자신이 취소되어야 하는지 확인
   Cancellation point에서 스레드를 cancel함

