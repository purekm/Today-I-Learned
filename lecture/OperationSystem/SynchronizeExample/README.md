Synchronization Examples
1.bounded-buffer
    counter 변수 없이 mutex만으로는 해결 불가능
    Counting semaphore 인 full,empty를 사용하는게 효율적
    생산자와 소비자가 별도의 mutex를 사용하는게 효율적

2.readers-writers
    여러 reader가 읽을 수 있고, writer는 혼자만 cs에 들어갈 수 있음
    공유 데이터
        data set
        reader와 writer 상호배타용 mutex
        reader의 reader_count 를 업데이트하기 위한 mutex
        read_count - 현재 진행 중인 reader
    reader 선호 알고리즘 - 대기하고 있는 reader와 writer가 있으면, reader가 우선적으로 실행
    writer 선호 알고리즘 - 대기하고 있는 writer와 reader가 있으면, writer가 우선적으로 실행
    공정한 reader

3.dining philosophers 
    deadlock 을 피하는 3가지 방법
    1.테이블에 최대 4명이 앉는다.
        한명은 항상 젓가락을 양쪽 다 잡을 수 있음
    2.젓가락을 둘 다 잡을 수 있을 때만 잡는다.
        모두 잡을 수 있을 때만 잡고, 아니면 다시 젓가락을 놓음
    3.짝수번 철학자는 왼쪽,오른쪽 순서로 젓가락을 잡고, 홀수번 철학자는 반대 순서로 잡는다.
        순서가 충돌하지 않음

Kernel level 동기화 메커니즘
1. Interrupt Masks(단일 프로세서)
    전역 자원에 대한 접근을 보호하기위해 사용
    인터럽트를 비활성화 하여 현재 실행 중인 코드가 인터럽트되지 않게 함
    단일에서 효율적
2. Spinlokcs(다중 프로세서)
    spinlock을 획득한 스레드는 절대로 preemption 되지 않음
        preemption되면 deadlock이 발생할 수 있음
    spinlock을 사용하면 짧은 시간 동안 busy-waiting을 유지하며 자원을 기다림
    작업이 짧을 때 효과적

3.Dispatcher object (User level 동기화 메커니즘이기도 함)
    mutex, semaphore, Event, Timer 등의 역할을 할 수 있음
    Event - 어떤 조건을 만족하면 기다리던 스레드에게 notify()
        조건 변수와 유사함
    Timer - 시간이 만료되면 하나 이상의 스레드에게 알림
    Dispatcher object에는 signaled-state와 non-signaled-state가 존재
    signaled-state - signal을 받은 상태로, Dispatcher마다 waiting queue가 존재하는데, ojbect가 signaled-state로 바뀌면  queue에 대기하던 일부 혹은 모든 스레드를 깨운다.
    non-signaled-state - thread가 block 된 상태

    mutex Dispatcher object
    signaled-state는 mutex가 사용 가능한 상태로, 대기 중인 스레드가 없고, 새로운 스레드가 mutex를 얻을 수 있음

Linux 동기화
Kernel 2.6 이전에는 인터럽트 비활성화를 통해 짧게 cs를 구현
Kernel 2.6 이후에는 완전한 preemptive 커널로 전환

동기화 도구
    Semaphore
    Atomic Integer
    Spinlokcs
    Mutex lock

단일 CPU 에서는 preemption 비활성화를 통해 동기화
    단일 processor에서는 interrupt 비활성화를 통해 동기화
    같은 의미인가?몽가?
다중 CPU 에서는 Spinlocks를 통해 동기화
Linux의 spinlock 과 mutex는 비재귀적이므로, 락을 획득한 상태에서 같은 락을 획득하려고 하면 deadlock 발생 


Kernel에 있는 task가 lock을 가지고 있으면 이 task는 non-preemptive하다.
현재 가지고 있는 lock의 수를 preempt_count라고 하면 preempt_count가 0이 되면 preemption이 가능하다.

Atomic variable
여러 스레드가 동시에 접근할 때도 안전하게 사용될 수 있는 변수
동기화 없이도 여러 스레드에서 안전하게 읽고 쓸 수 있도록 설계되어 있음

atomic_init(&a,0): 원자적 변수 초기화
int value = atomic_load(&a): 원자적 변수 값 읽기
atomic_store(&a,20): 원자적 변수에 값을 저장
int old_value = atomic_exchange(&a,15): 원자적 변수의 값 교환,바뀌기 전 값을 return 
if(atomic_compare_exchange_strong(&a,&expected,desired))
    a와 expected가 같으면 return true 후 desired과 값 변경
    a와 expected가 다르면 return false 후 expected에 object의 값이 저장 됨
while(atomic_compare_exchange_weak(&a,&expected,desired))
    strong과 같은 효과지만, 가끔 틀린 결과가 나올 수 있어서 while문에 넣어서 계속 확인
 int old_value = atomic_fetch_add(&a, 10): a에 값을 더함
 int old_value = atomic_fetch_sub(&a, 5) : a에 값을 뺌
 int old_value = atomic_fetch_and(&a, 0b1010) : a와 and 연산 0b는 이진수를 나타냄

POSIX 동기화 도구 
    mutex
    Semaphore
    Condition variable

UNIX,Linux,macOS에서 널리 사용됨
    Mutex
        int pthread_mutex_destroy(&mutex);
        int pthread_mutex_init(&mutex,NULL);
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        int pthread_mutex_lock(&mutex);
        int pthread_mutex_trylock(&mutex);
        int pthread_mutex_unlock(&mutex);
        int가 붙은 이유는 반환 값이 int type이기 때문이다.
    
    Semaphore
        named semaphore - 관계없는 프로세스간에도 공유 가능
        unnamed semaphore - 같은 프로세스내의 스레드간에만 공유 가능
        
        sem_t *sem_open(const char *name, int oflag); //세마포어 생성 or 열기
        sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
        int sem_close(sem_t *sem); //세마포어 닫기
        int sem_unlink(const char *name); //named 세마포어 제거
        int sem_init(sem_t *sem, int pshared, unsigned int value); //unnamed semaphore 초기화 pshared == 0 이면 같은 프로세스 내에서 공유, pshared != 0이면  프로세스 사이에서 공유하며 memory공간에 있어야함.
        int sem_destroy(sem_t *sem); //unnamed 세마포어 제거
        int sem_wait(sem_t *sem); //semaphore를 기다린다. semaphore가 0보다 크면 감소시키고, 그렇지않으면 클 때 까지 대기
        int sem_trywait(sem_t *sem); //즉시 세마포어를 시도한다.
        int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);//timeout이후에도 세마포어가 사용가능해지지않으면 실패
        int sem_post(sem_t *sem);//세마포어의 값을 증가시킨다. 기다리는 스레드가 있으면 깨워준다.
        int sem_getvalue(sem_t *sem, int *sval); //세마포어의 현재 값을 가져온다.

    Condition variable
        Posix 조건 변수는 상호배타가 필요하다.(mutex) 
        pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 조건 변수 초기화
        int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex); // 조건 변수 wait
        int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime); //지정된 시간까지 기다리고 시간 초과되면 실패
        int pthread_cond_signal(pthread_cond_t *cond); 대기 중인 스레드 중 하나를 깨움
        int pthread_cond_broadcast(pthread_cond_t *cond); // 대기 중인 모든 스레드를 깨움
    조건 변수는 while문을 통해서 조건을 다시 검사하는 것이 매우 중요하다.
        cond_wait()에서 mutex_lock을  풀기 때문에, 리턴되었을 때 a나b의 값이 변경되어 있을 수 있기 때문이다.
    



