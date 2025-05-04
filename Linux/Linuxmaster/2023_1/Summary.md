커널 컴파일은 4단계로 이루어짐
청소 -> 설정 -> 이미지 생성(build) -> 모듈 컴파일
mrproper / distclean -> menuconfig -> bzimage -> modules
mrproper
menuconfig
bzimage
modules

ext 계열은 fsck으로 점검하고, xfs는 repair로 검사함 

-D 옵션을 사용하면 default로 되어있는 환경설정 파일을 변경한다는 뜻  
-b 는 홈 디렉터리 경로 지정  
-d 는 특정 사용자만을 위한 홈 디렉터리 저장하고 싶을 때 

포트 스캔은 열려있는 포트를 찾는 것  
Well Known Port는 0~1023번에 해당  
nmap을 가장 많이 사용
1. nmap
2. -p 0-1023

메일 별칭을 사용하여 특정 계정으로 온 메일을 다른 사용자에게 전달하는 방법  
이때 사용하는 것은 /etc/aliases  
설정 후에는 newaliases 명령어로 갱신해야 함  
다른 파일에 있는 사용자 목록을 참조하고 싶을 때는 :include: 사용

NFS는 서버의 디렉터리를 다른 클라이언트가 네트워크를 통해 마운트해서 사용할 수 있게 해주는 서비스
NFS 서버 설정 파일은 /etc/exports

Zone 과 Service 개념을 기반으로 방화벽 정책 관리
firewall-cmd 로 명령
웹 서비스를 public 영역에 설정하고, 재부팅 후에도 적용되게 해야 함
Zone : public
Service : http
영구 적용 : --permanent
즉시 반영 : --reload

smbclient -L 은 서버의 공유 리스트를 보여줌
smbclient //서버IP/공유 이름
//192.168.5.13/data
testparm

/etc/fstab
파일 시스템에 대한 다양한 정보를 담고 있는 파일
부팅 시 마운트 할 파티션 정보가 기록되어 있음
mount, fsck가 수행될 때 이 파일의 정보 참조
fstab 파일은 장치, 마운트 지점, 파일 시스템, 마운트 옵션, 덤프 여부, fsck 순서로 총 6개의 필드로 구성됨.  
사용자 쿼터 제한은 usrquota
그룹 쿼터 제한은 grpquota
쿼터 정보를 초기화/생성하는 명령어는 quotacheck