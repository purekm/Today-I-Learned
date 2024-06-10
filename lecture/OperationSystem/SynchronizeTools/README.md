Synchronization Tools

프로세스는 동시에 실행 가능
busy waiting 상태 - 계속 CPU를 소모하는데 waiting중인 상태 
race condition - 경쟁 상태로 인해 원치않은 결과가 발생할 수 있기 때문에 상호 배타가 필수적 
critical section - 임계 구역으로, 공유 자원을 사용하는 구간을 나타냄

컴파일러는 비종속적인 두 명령어의 순서를 임의로 바꿀 수 있다.

Critical section 문제 해결책
1. 상호배제 
2. progress - 어떤 프로세스도 cs를 실행 중이지 않으면 , 대기중인 프로세스 중 하나는 선택되어야한다. 무기한 연기될 수 없음
3. bounded waiting - 한 프로세스가 cs에 들어가면 다른 프로세스가 cs에 들어가는 횟수는 제한되어야 한다.

OS는 커널이 선점 가능한지 여부에 따라 두가지 접근 방식을 취할 수 있다.
preemptive , Non preemptive로 나뉜다.

피터슨 solution

Synchronization Hardware
많은 시스템은 cs를 구현하기 위해 하드웨어 지원을 제공

단일 프로세서 - 인터럽트를 비활성화 가능

3가지 형태의 하드웨어 지원
1. 메모리 배리어
    strongly ordered - 프로세서의 메모리 수정이 즉시 다른 프로세서에게 보임
    weakly ordered - 메모리 수정이 다른 프로세서에게 즉시 보이지 않음

    while(!flag)
        memory_barrier();
    print x

    위의 경우에는 x값이 로딩되기 전에 flag 값이 먼저 로딩되는 것을 보장함 
    very low-level 이므로, 커널 개발자가 특별하게 상호 배타하는 경우만 사용

2. 하드웨어 명령어
    Test-and-Set
        while(test_and_set(&lock))
            lock 값을 true로 만들어주고 설정 전 lock 값을 리턴
            리턴 값이 true면 cs에 다른 프로세스가 있다는 의미
            리턴 값이 false면 cs에 아무도 없다는 의미
                lock이 false면 cs에 들어가고 true로 바꿔 줌으로써 다른 프로세스가 cs에 들어오지 못하게 함
        while문에서 lock 획득을 계속 시도하고 있으므로 spin-lock
        spin-lock - lock을 얻기 위해 CPU 소모를 계속 하는 상태

    Compare-and-Swap
        while (compare_and_swap(&lock, expected, new_value) != 0)
            lock값과 expected의 값이 같으면 lock의 값을 new로 변경
            둘의 값이 다르면 변화 없음
            항상 lock의 original 값을 return
        while (compare_and_swap(&lock, 0, 1) != 0)
            처음엔 lock이 0이였다가, 한번 실행하면 lock이 1로 바껴서 대기상태로 바뀐다.
            처음에 실행되었던 프로세스가 lock 풀어주면 lock이 0으로 바껴서 다음 프로세스가 실행된다.
            lock 획득을 계속 시도하고 있기 때문에 spin-lock
            의미적으로 test-and-set과 동일

    Comapre-and-Exchange
        while (!compare_and_exchange(&lock, &expected, new_value))
            lock 값이 expected값과 일치하면 new_value로 바꾸고 return true
            일치하지 않으면 expected 값을 lock 값으로 바꾸고 return false
        while (!compare_and_exchange(&lock, &expected, 1)) 
            의미적으로 test_and_set과 동일하며, spin-lock 방식이다.
        
        waiting queue를 이용한 peterson 방식을 compare_and_swap 과 함께 사용하면
        CS에 순차적으로 들어가는 알고리즘 구현 가능
        while (true) {
            waiting[i] = true;
            key = 1;
            while (waiting[i] && key == 1)
                key = compare_and_swap(&lock, 0, 1);
            waiting[i] = false;
            // 임계 구역
            j = (i + 1) % n;
            while ((j != i) && !waiting[j])
                j = (j + 1) % n;
            if (j == i)
                lock = 0;
            else
                waiting[j] = false;
            // 나머지 구역
        }
    
3. atomic 변수

    while(!atomic_compare_exchange_weak(&lock, &expected, 1))
    Weak 버전은 object와 expected가 같아도 false를 반환하는 거짓 부정이 가능
    Strong 버전은 거짓이 없으나 느리다. IF문 안에서 사용함.

mutex
lock을 얻고, 해제하는 방식
mutex의 acquire()과 release는 원자적으로 구현할 때 주로 atomic_instructions에서 compare-and-swap을 사용
compare-and-swap은 busy waiting방식이므로, spin-lock이라 불림
spinlock은 CPU를 소모하지만 context switching이 필요없어서 유리한 면이 있음.
lock을 걸고 있는 시간이 두 개의 context switching 시간보다 작으면 spinlock이 유리함.

Semaphore
mutex의 정교한 버전
Semaphore S - int S>0이면 CS에 들어갈 수 있음
세마포어는 활용할 수 있는 자원의 수 라고 생각하면 편함
wait()와 signal() 함수로 S를 조절한다.
wait(S)는 while(S<=0) 일 동안 wait하고, S--한다.
signal(S)는 S++
Binary semaphore은 mutex lock과 같음
프로세스가 CS에 오래 머물지 않을 때 유리함

Busy waiting 이 없는 semaphore
block 연산을 통해 호출한 프로세스를 대기 큐에 배치한다.
wakeup 대기 큐에서 하나의 프로세스를 제거하고 레디 큐에 배치한다.

단일 CPU 버전
wait(S){
    disable interrupts
    S->value--;
    if(S->value<0){
        add this process to S->list;
        block(); //호출한 프로세스를 대기 큐에 배치
    }
    enable interrupts
}

signal(S){
    disable interrupts
    S->value++;
    if(S->value<=0){
        remove a process P from S->list;
        wakeup(P); //대기 큐에 있던 프로세스 중 하나인 P를 제거하고, 레디 큐에 넣음
    }
    enable interrupts
}
단일 CPU 버전에서는 interrupts를 비활성화하여 원자성 구현
하지만 다중 코어에서 인터럽트로 전부 막는 것은 비효율적
-> 스핀락을 통해 상호 배타성 보장
다중 CPU버전
wait(S){
}

다중 CPU버전
wait(S){
    while(test_and_set(&mutex)){
        ;
    }
    S->value--;
    if(S->value<0){
        add this process to S->list;
        mutex = false;
        block(); //호출한 프로세스를 대기 큐에 배치
    }else 
        mutex = false;
}

signal(S){
    while(test_and_set(&mutex)){
        ;
    }
    S->value++;
    if(S->value<=0){
        remove a process P from S->list;
        mutex = false;
        wakeup(P); //대기 큐에 있던 프로세스 중 하나인 P를 제거하고, 레디 큐에 넣음
    }else 
        mutex = false;
}

Conditional variable 조건 변수
wait() 조건 변수가 signal을 받을 때까지 대기
signal() 대기 중인 스레드 중 하나를 다시 실행. 아무도 대기하고 있지 않으면 효과X

Semaphore 과 Conditional variable 의 차이점
Semaphore.wait()는 세마포어 값이 0보다 크면 --, 0이면 대기
Semaphore.signal()은 세마포어 값을 증가시키고, 만약 대기중인 스레드가 있으면 하나를 깨움

조건 변수를 사용하는 이유는 스레드가 busy waiting 상태가 되어 CPU 자원을 낭비하는 것을 막기 위함
조건 변수는 스레드를 일시 정지시키고, 다른 스레드가 조건을 충족시킬 때 까지 기다리게 함

monitor
모니터는 프로세스 동기화를 위한 편리하고 효과적인 메커니즘을 제공하는 고수준 추상화
추상 데이터 타입으로, 내부 변수는 절차 내의 코드에 의해서만 접할 수 있다.
모니터 내에서는 하나의 프로세스만 활성 상태일 수 있다.
실행 중인 프로세스가 더 이상 진행할 수 없으면 조건 변수를 사용하여 스스로 suspend할 수 있다.
외부에서 모니터 함수를 사용하여 접근 가능

모니터안에서 프로세스를 병렬으로 실행시키고 싶으면, 조건 변수에 wait()를 실행함으로써 가능
wait()를 원하는 지점에 사용함으로써 preemption 위치를 스스로 정할 수 있다.

monitor ExampleMonitor {
  // 공유 변수 선언
  private int sharedVariable; //함수에 의해서만 접근할 수 있다. 외부 코드에서 접근할 수 없음.
  // 모니터 내에서만 접근 가능한 함수들
  public void increment() {
    sharedVariable++;
  }

  public void decrement() {
    sharedVariable--;
  }

  public int getValue() {
    return sharedVariable;
  }
}
monitor을 통해서 동기화 문제를 쉽게 해결 가능

여러 프로세스가 대기 중일때, signal로 어떤 프로세스를 다시 실행할지 결정하는 방법
FCFS - 항상 적절하지 않을 수 있음
우선순위 기반 - 조건 변수를 사용할 때 우선 순위를 지정할 수 있는 x.wait(c) 형태의 조건부 대기 사용가능 

Single Resource Allocation - 모니터를 이용한 자원 할당기

monitor ResourceAllocator 
    { 
    boolean busy; 
    condition x; 
    void acquire(int time) { 
        if (busy) 
            x.wait(time); //프로세스가 자원을 사용하는 시간이 짧은 것에 우선순위를 주는 사례
        busy = true; 
    } 
    void release() { 
        busy = FALSE; 
        x.signal(); 
    } 
    initialization code() {
        busy = false; 
        }
    }

Signal and wait - P는 Q가 모니터를 떠날 때까지나 다른 조건을 기다리고 있을 때까지 wait한다.
function F ( . . . ) 모니터함수 
{
    wait(mutex); 상호배타 확보
    ...
    body of F
    ...
    if (next_count > 0)
        signal(next);
    else
        signal(mutex);
} 
x.wait()
{
    x.count++; 
    if (next_count > 0)
        signal(next);
    else
        signal(mutex);
    wait(x.sem); x가 signal을 받을 때 까지 대기
    x.count--; 
}
x.signal()
{
    if (x.count > 0) { 조건 변수를 기다리는 프로세스가 있다면
        next_count++; 
        signal(x.sem); 조건 변수 x를 깨워줌
        wait(next); 깨워준 x를 next
        next_count--;
    }
}


Liveness
시스템이 특정 조건을 만족하면서 프로세스들이 무한정 기다리지 않고, 적절히 진행될 수 있도록 보장하는 속성
Liveness failure 의 예시
1. Deadlock 상태 
2. Starvation 상태
3. 우선순위 역전 상태 
    해결 방안으로 priority-inheritance protocol 사용
    현재 자원을 소유한 낮은 프로세스가 자원을 요청한 높은 프로세스의 우선순위를 임시하로 상속받아 실행되는 행위 

Liveness 속성
1.Progress - 시스템은 항상 어떤 프로세스가 진행될 수 있는 상태여야함
2.Bounded_waiting - 각 프로세스는 유한한 시간 내에 반드시 진행될 수 있어야 함