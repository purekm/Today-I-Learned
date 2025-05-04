사용자관리

    /etc/skel은 새 사용자를 만들 때 그 사용자의 홈 디렉터리에 복사되는 기본 파일들이 저장된 디렉터리
    /etc/skel/www는 default 디렉터리 설정를 www로 설정

SELinux

    getenforce를 사용하면 Enforcing 모드인지, Permissive 모드인지 알 수 있음
    setenforce 0 이면 비활성화(Permissive)
    setenforce 1 이면 활성화(Enforcing)
    이것들은 일시적인 활성화 및 비활성화이고,
    /etc/selinux/config 파일을 수정하면 영구적