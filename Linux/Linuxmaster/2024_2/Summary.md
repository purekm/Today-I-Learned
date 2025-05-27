usermod -L -e 2024-12-31 -f 3  
 usermod : 사용자 계정 관리(셸, 홈 디렉터리, 그룹, UID, GID 등 대부분의 정보 변경 가능)   
 - l : 사용자 아이디 변경(--login) 
 - d : 사용자의 홈 디렉터리 변경(--home)  
 - m : 기존에 사용하던 파일, 디렉터리 그대로 옮겨오도록 설정(--move-home)   
 - G : 추가로 다른 그룹에 속하게 함  
 - L : 사용자의 로그인 일시 정지(--lock)  
 - e : EXPIRE_DATE(yy-mm-dd)에 계정 만기(--expiredate)  
 - f : 패스워드 만기일이 지난 후 패스워드에 Lock 설정할 유예 기간 지정(--inactive)  
 - g : 사용자의 그룹 변경  
 - s : 사용자의 셸 변경 
 - u : 사용자의 UID 값 변경 

dd는 디스크/파티션/파일의 바이너리 수준 복사
 - 디스크 복제
 - if=FILE 은 input file이고, of=FILE 은 output file

dump는 파일 시스템의 백업
 - 전체 파일 시스템 백업 (ext)
 - 0 ~ -9	: 백업 레벨 지정  
 - 0 : 전체 백업  
 - 1~9 : 증분 백업  
 - f [파일명]	: 백업을 저장할 파일 지정 (-f home.xdump)  
 - u : 백업 날짜를 /etc/dumpdates에 기록  
 - h [숫자] : 백업 보존 레벨 지정 (디폴트: 1)  
 - b [숫자] : 블록 크기 지정 (기본은 512바이트)  
 - B [숫자] : 한번에 쓰는 최대 블록 수  
 - W : 백업이 필요한 파일시스템을 보여줌  
 - w : 오늘 백업이 필요한 파일시스템만 보여줌

restore [옵션] [백업파일명]
 - r : 전체 복원 (restore entire dump)  
 - t : 복원 전에 트리 구조만 출력  
 - x : 특정 파일/디렉토리만 복원 (경로 지정 가능)  
 - i : 대화형(인터랙티브) 모드로 복원  
 - f : 입력 파일 지정 (dump 파일)  
 - C : 현재 디렉토리에서 복원 (기본 동작과 유사) 

rsync는 디렉토리 복사 및 서버 간 파일 전송  
 - a 옵션은 퍼미션, 타임스탬프, 소유자 등 보존  
 - v 진행상황  
 - z 전송 중 압축  

cpio는 아카이브 생성/해제(파일리스트 기반) tar과 유사함
 - 여러 파일 묶기, 이동/복사/백업
 - ovF (o는 백업 생성, v는 진행 상황출력, F는 파일 이름 설정)
 - tF(t는 백업된 내용 출력)
 - ivF(i는 백업된 내용 추출)
 - c portable ASCII format 사용 
 - d 디렉터리가 없으면 자동으로 생성 
tar
 - c (create)는 새로운 tar 파일 만들기
 - f (file)은 파일 이름 지정
 - 파일 이름 obj.tar을 설정하고, 뒤에 묶을 파일 목록 *.o 를 적는다. 

nice -n -39 bash  
renice -n -10 -p 1999   
renice -20 1999

tar 

    Jxvf  
    J는 xz 형식 지원  
    x는 압축해제  
    v는 진행상황 보기  
    f는 파일 지정  

커널 메뉴 기반 인터페이스 설정 - make menuconfig  
커널 이미지 빌드 - make bzimage
모든 커널 모듈 간의 의존 관계를 기록한 정적 파일
/lib/modoules/(uname -r)/modules.dep

vgscan

    볼륨그룹 탐색  
    lvscan  
    pvscan

ssh

    scp - 보안 파일 복사  
    sftp - 파일전송  
    ssh-add - 개인 키를 ssh-agent에 추가  
    ssh-agent - ssh 인증 에이전트  
    ssh-copy-id - 로컬에 있는 공개 키를 원격 서버에 복사하여 인증 자동화  
    ssh-keygen - SSH 키쌍 생성 도구  
    ssh-keyscan - 원격 서버의 ssh 공개 키를 수집  

apache

    /usr/local/apache/bin/ : 실행 파일 (apachectl, httpd 등)  
    /usr/local/apache/conf/	: 메인 설정 파일 (httpd.conf)  
    /usr/local/apache/conf/extra/ : 서브 설정 파일 (httpd-userdir.conf 등)  
    /usr/local/apache/modules/ : .so 모듈 파일

grep   

    -r : 디렉터리를 탐색하며 모든 파일 검색  
    -i : 대소문자 구분X  
    -ri를 주로 사용  

vsftpd

    FTP 서버 설정  
    /etc/vsftpd/vsftpd.conf : vsftpd의 환경 설정 파일  
    /etc/pam.d/vsftpd : vsftpd의 PAM 관련 설정 파일  
    /etc/vsftpd/ftpusers : PAM 관련 설정파일에 사용되는 파일이고, default로 접근 거부될 사용자 목록  
    /etc/vsftpd/user_list : vsftpd를 이용하는 사용자 목록 파일이며, 허가 및 거부 목록으로 사용가능함. 하지만 기본 설정은 deny여서 거부 목록 파일  
    /etc/logrotate.d/vsftpd : vsftpd의 로그 로테이트 관련 파일  
    weekly  
    minsize 1M   
    create 0600 root utmp   

mail

    rsyslog.conf - 메일로그 관련  
    mail.debug - 로그 레벨 설정
    find로 경로 찾을 때 2>/dev/null을 작성하면 에러없이 답만 출력해줌  
    *.=crit;kern.none - critical만 기록, 커널에는 X  
    로그를 원격 서버로 전송 : @@192.168.5.13 (TCP)  
    로그 입력 → logger    
    일반 메시지 → /var/log/messages    
    로그인 성공 → last, who, /var/log/wtmp    
    로그인 실패 → lastb, /var/log/btmp  
    인증 관련 → /var/log/secure  
    설정 보기 → /etc/rsyslog.conf  

    메일 서버 관련 패키지는 sendmail  
    rpm - qc sendmail 으로 주요 환경설정 파일 찾기  
    virtusertable은 하나의 메일 서버에 여러 도메인을 함께 사용하는 환경에서 한 계정을 다른 계정으로 포워딩할 때 사용됨  
    /etc/mail/local-host-names : 최종 수신지 도메인 설정  
    /etc/mail/sendmail.cf : 발신 도메인 설정  
    /etc/mail/access : 메일 Relay 제한 및 스팸메일 방지 설정, 메일 서버로 접근하는 호스트나 도메인 접근 제어  
    - RELAY : 중계 허용  
    - REJECT : 메일 거절 메시지를 보냄  
    - DISCARD : 무조건 거절  
    - OK : DNS 조회가 되지 않은 경우라도 메일 허가  
    /etc/alias 는 admin 같은 로컬 이름을 리디렉션
    /etc/mail/virtusertable : user@naver.com 같은 외부 주소 전체를 매핑  
    /etc/mail/sendmail.mc   
    makemap은 텍스트 테이블 파일을 .db 형태로 변환함  

DNS

    /etc/named.conf : 도메인 설정 파일  
    /var/named/도메인.zon : forward zone(도메인 -> IP)
    /var/named/도메인.rev : reverse zone(IP -> 도메인)
    /etc/resolv.conf : 클라이언트 DNS 설정
    /etc/hosts : DNS보다 우선시 되는 고정 IP-호스트 매핑

    SOA : 도메인에 대한 기본 정보 및 관리 책임자 (IN SOA ns.example.com. admin.example.com.)  
    NS : 네임서버 지정 (IN NS ns.example.com.)  
    A : 도메인 -> IP 주소 매핑 (www IN A 192.168.0.10)  
    PTR : IP주소 -> 도메인 (10 IN PTR www.example.com.)  
    MX: 메일 서버 지정 (@ IN MX 10 mail.example.com.로 MX뒤에 숫자는 우선순위를 나타냄)  
    CNAME : 별칭 레코드

    Zone 선언은
    정방향(Forward Zone)은 도메인 이름
    역방향(Reverse Zone)은 IP 주소를 거꾸로 (3번째 옥텟 기준) + .in-addr.arpa를 사용

    형식:
    zone "도메인명" IN {
        type master;
        file "파일명";
    };

    zone "역방향 네임" IN {
        type master;
        file "역방향 파일명";
    };
    master는 내가 주인일 때, slave는 복사본을 관리할 때 사용

dhcp   

    /etc/dhcp/dhcpd.conf : 메인 설정 파일
    /var/lib/dhcpd/dhcpd.leases : 임대 기록 저장 파일
    /etc/sysconfig/dhcpd : 서비스 포트/인터페이스 설정

    option routers 192.5.1; : 기본 라우터 설정  
    option domain-name-servers 192.168.5.13 : DNS서버 설정  
    option domain-name "kait.or.kr" : 도메인 네임  
    default-lease-time 7200 : 기본 임대 시간  
    max-lease-time 14400 : 최대 임대 시간  
    option broadcast-address : 192.168.12.255 서브넷 브로드캐스트  
    option subnet-mask 255.255.255.0 : 서브넷 마스크  
    subnet 192.168.12.0 netmask 255.255.255.0 : 서브넷 범위  
    range 192.168.12.100 192.168.12.200

    sudo systemctl start dhcpd  
    sudo systemctl enable dhcpd  
    sudo systemctl status dhcpd  
    dhcpd -t : 설정 문법 검사 

    host client1 {
    hardware ethernet 00:11:22:33:44:55;
    fixed-address 192.168.12.50;
    }

IPtables

    -t : 테이블 종류 (기본은 filter, Nat는 nat)  
    -A : 체인에 규칙 추가(Input, output, forward, prerouting, post routing)  
    -j : 동작 지정(Accept,Drop,Dnat(패킷 도착지 주소 변경),Snat(패킷 발신지 변경),Masquerade)  
    -F : 초기화(Flush)  
    -N : new chain
    -L : 규칙 확인   
    
    filter : Input, Output, Forward - 기본 방화벽  
    nat : Prerouting, Postrouting, Output - NAT, 포트 포워딩  
    mangle : 모든 체인 - 패킷 수정  
    raw : Prerouting,Output  

    -L : 모든 체인(rule) 보기
    -n : 숫자로 보여줘 (IP, 포트 이름 대신 숫자)
    -v : 패킷/바이트 수까지 자세히
    --line-numbers : 번호 붙여서 출력

    iptables-save > firewall.sh : 현재 설정되어 있는 규칙을 firewall.sh 파일에 저장
    iptables-restore < firewall.sh : 파일에 저장되어 있는 규칙을 불러와서 반영

xinetd

    only_from = 192.168.12.22 192.168.5.0
    no_access = 192.168.5.44 192.168.4.2
    instances = 30
    per_source = 3
    access_times = 09:00-18:00, 20:00,23:30

    
