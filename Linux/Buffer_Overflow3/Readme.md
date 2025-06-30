ASLR 원리
- 공격자가 스택 주소나, EBP, 쉘코드 주소 등 정확히 예측하지 못하게 함
- 프로그램 실행마다 스택 시작 위치를 무작위로 변경함

ASLR 우회 방법
- ASLR 켜기
- Set-UID bit 설정
- 취약한 프로그램을 무한 루프로 실행 -> 언젠가는 랜덤 주소가 일치할 것

StackGuard
- 컴파일러가 canary 값을 return address 앞에 삽입하여, 함수 종료 시점에 canary 값이 변경되었는지 확인 
- 변경되었으면 스택 오버플로우 탐지 및 감지

Non-Executable Stack 사용

bash & dash는 Set-UID로 실행되어도, RUID로 실행됨.
=> setuid(0)를 쉘코드랑 같이 실행함으로써 root 권한으로 되돌림
=> root shell 획득 가능

