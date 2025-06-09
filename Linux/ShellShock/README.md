Shell program은 OS에서 command-line interpreter임

shell function을 export해서 자식 프로세스에 inherit 하는 방법도 있고,
shell 변수를 export 한 다음에 bash가 취약한 경우에는 function이 inherit됨.

Shellshock Vulnerability
![alt text](image.png)

취약한 bash의 파싱 로직에 있는 오류로 인해서 변수에 포함된 command을 실행시킴
함수에 포함되는게 아니라, 실행되는 것

![alt text](image-1.png)

vul을 실행시키면, 내부에서 bash가 환경변수 foo를 함수로 등록하려다가 /bin/sh도 실행함
=> bash를 결국 root 권한으로 실행하게되어 root 셸을 얻게 되는 것

ShellShock Attacks on CGI Program
![alt text](image-2.png)


CGI는 웹 서버가 외부 프로그램을 실행해서 동적으로 HTML 생성하는 기술

먼저 사용자가 HTTP 요청을 보내면, Apache는 fork를 통해 새로운 자식 프로세스 생성
자식 프로세스는 exec() 호출로 CGI 스크립트를 실행하는데,
CGI 스크립트는 맨 위에 #!/bin/bash로 시작함
=> bash로 실행해라는 의미
exec()는 결국 bash 프로그램을 실행
=> bash를 사용하면 아까처럼 shellshock 발생
=> 결국 사용자 요청만으로도 서버에서 bash가 root 권한으로 악성 명령을 실행

![alt text](image-3.png)

실행 결과로 /bin/ls -l 이 실행됨
보통 아파치 웹 서버는 낮은 권한 사용자로 실행되기 때문에 root 탈취는 불가능함
하지만 정보를 읽는 것 까지는 가능함

![alt text](image-4.png)

비밀번호는 대부분 파일에 하드코딩되어 있는데, cat을 통해서 출력
이를 통해 DB 비밀번호를 탈취함

Reverse Shell
서버에서 명령어를 실행할 수 있는 쉘을 공격자에게 연결시켜주는 것
