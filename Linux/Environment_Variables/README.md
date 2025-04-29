How to Access
![alt text](image.png)
main 함수의 envp[] 인자는 항상 보장되지 않기 때문에, 전역변수로 하는게 좋음.

Meomory location
![alt text](image-1.png)
envp와 environ은 처음에 같은 공간을 가리리킴
envp는 메인 함수에만 접근 가능하며, environ은 전역변수라서 모두 접근 가능
환경 변수에 변화가 생기면, 환경 변수를 위치는 힙으로 이동함(envp는 옛날 주소를 가리킴)

Shell Variables & Environment Variables
Shell variables는 shell 내부에서만 사용하는 변수
Shell은 variables를 생성 및 제거할 built-in command 제공

![alt text](image-2.png)
Shell 변수와 Environment Variables는 초기에 같지만, shell 변수의 변화는 environment 변수에 반영되지 않음

![alt text](image-3.png)
Shell 변수는 Environment 변수의 자식 프로세스에 영향을 미칠 수 있음
shell 변수 따로 설정한 것을 export하면 shell 변수가 environment 변수로 승격하여 shell 변수는 자식 environment 변수 프로세스의 부모가 됨

![alt text](image-4.png)
초기에 environment 변수인 LOGNAME=seed는 shell도 가지고 있었는데,
shell변수로 LOGNAME2를 지정해주고, LOGNAME3를 export했음.
LOGNAME3는 export 했기 떄문에 환경변수로 설정되어서, env | grep LOGNAME을 하면 LOGNAME과 LOGNAME3가 출력됨

Attacks via Dynamic Linker
Linking은 runtime or compile time에 실행됨

![alt text](image-5.png)
Static linking은 파일 크기가 Dynamic linking의 100배정도 됨

![alt text](image-6.png)
프로그램을 컴파일하기전에 , excutable(Partially Linked)이 메모리에 먼저 load됨

![alt text](image-7.png)
ldd command를 통해 프로그램이 어떤 라이브러리에 의존하는지 알 수 있음
처음엔 system call을 나타내고,
둘째줄은, libc 라이브러리를 뜻하며
마지막 줄은 dynamic linker를 뜻함

Risk of Using Dynamic Linker
![alt text](image-8.png)
Dynamic Linker는 메모리를 아껴줌
=> 프로그램 코드의 일부가 컴파일할 때 undecided 된 상태라는 의미
사용자가 missing code(결정되지 않은 부분)을 조작하면 문제가 발생함

Case Study 1:
LD_PRELOAD는 지정한 공유 라이브러리를 가장 먼저 로딩하게 함
=> 사용자가 만든 가짜 라이브러리를 먼저 실행시킬 수 있게 됨

LD_LIBRARY_PATH는 사용자가 특정 경로를 추가해 원하는 라이브러리를 먼저 실행할 수 있게 함
=> 공격자가 만든 코드를 먼저 실행할 수 있게 됨

Set-UID 프로그램의 경우 일반 사용자가 실행해도 root 권한으로 동작함
=> 만약 LD_PRELOAD로 조작되면, root 권한으로 악성 코드가 실행될 수 있음


![alt text](image-9.png)
sleep.c 파일에서 함수를 조작하고, 공유 라이브러리로 만들어서 PRELOAD environment variable에 추가했음
이 경우, 조작된 " I am not sleeping "이 출력됨

요세미티에서 동적 링커(dyld)는 새로운 환경 변수인 DYLD_PRINT_TO_FILE 도입
이 변수는 동적 링커의 로그 출력을 지정된 파일로 리디렉션하는 기능을 함
이 기능이 도입이 될 때, 보안상 필수 검증이 누락되어 Set-UID 루트 바이너리에서도 환경변수가 사용될 수 있는 문제가 발생
=> 이를 악용하면 공격자가 시스템의 임의의 위치에 루트권한으로 파일 생성 or 수정하거나 시스템 보안을 위협함

Question1:
env는 현재 쉘 환경변수 목록 출력
printenv는 환경 변수만 출력
set은 쉘 변수 + 환경변수 출력
![alt text](image-10.png)
처음 쉘 변수를 만들었을 땐, 환경변수가 아니므로 env | grep에 출력되지 않음
이후 export VAR1을 함으로써, VAR1은 환경 변수가 됨
VAR3는 처음부터 환경변수로 만들어짐

Question2:
execvp()나 execlp()는 내부적으로 execve()를 호출하지만, 전역 변수인 environ을 사용하기 때문에 환경 변수를 자동으로 전달한다.
하지만 execve()는 환경 변수 배열을 직접 인자로 받아 사용하기 때문에, 이를 명시적으로 전달해주어야 하며, envp가 NULL이면 환경 변수 없이 실행된다. 

Subtask1:
HANYANG 환경변수의 값으로 학번 설정하기
![alt text](image-13.png)

Subtask2:
부모의 환경변수와 자식의 환경변수를 비교한 테스트
![alt text](image-14.png)
아무런 출력이 나오지 않는걸로 보아, 같은 내용인 것을 확인할 수 있다.
이를 통해 자식은 부모의 환경변수를 상속받는다는 것을 알 수 있다.

Task1:
![alt text](image-15.png)
PATH, HANYANG, LD_LIBRARY_PATH 환경변수를 설정하고, grep을 해보았다. 
HANYANG과 PATH는 출력되었지만, LD_LIBRARY_PATH는 출력되지 않았다. 내 생각엔 Set-UID를 설정하고 실행할때, EUID과 RUID가 달라서 리눅스 자체 보안 메커니즘이 LD_LIBRARY_PATH를 무시한 것 같다.

Task2:
![alt text](image-16.png)
PATH 환경 변수 조작을 이용한 외부 명령어 공격이다.
공격을 하기 위해 보안이 취약한 zsh을 사용했다.
PATH 변수를 설정해줬는데, ".:"을 사용한다는 것은 현재 디렉토리에 있는 파일을 먼저 실행한다는 뜻이다. ls 라는 공격 파일을 생성하고, 이에 root 권한과 Set-UID를 설정해주었다. 
이후 ls를 실행했을 때, 정상적인 ls가 아니라 공격파일인 ls를 통해 root 셸을 얻을 수 있게 되는 것이다. 

Task3:
![alt text](image-17.png)
$ gcc -fPIC -g -c mylib.c
$ gcc -shared -o libmylib.so.1 mylib.o -lc
$ export LD_PRELOAD=./libmylib.so.1 
를 먼저 실행해주었다. 이는 mylib의 object 파일을 생성해주고, 이를 공유 파일로 생성했다.처음 myprog를 실행했을 때는, 공격이 의도한대로 가짜 파일을 실행시켰다. 하지만 Set-UID가 설정되어 있는 경우에는, 사용자가 실행했을 경우 EUID와 RUID가 다르기 때문에 리눅스에서 환경변수를 무시한다. 그래서 정상적인 sleep가 실행되었다.
마지막으로 sudo su를 통해 root가 되고 난 이후에는 EUID와 RUID가 같기 때문에 의도한대로 가짜 파일이 실행되어 I'm not sleeping이 출력된다.