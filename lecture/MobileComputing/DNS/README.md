Domain Name System
-	Properties of DNS
-	Hierarchical 한 구조로 파일들을 정리할 수 있게 나누자
-	Root 아래 계층에 존재하는 server를 Zone or Authoritative server이라고 함
-	Hierarchy of DNS server
-	Root 존재하지만, unnamed-root server(절대 꺼지면 안되니까 hardwired)
-	Top level domain(TLD) server – Root 바로 밑에 있는 servers 중 몇 server
-	DNS server와 소통할 수 있도록 하는 resolver software
-	Resolver는 cash에 있는지 확인해보고, 없으면 server로 감
-	거꾸로, IP주소로 hostname을 찾는 것이 가능(Reverse lookups)
    Root -> TLD -> Second-Level Domain -> SubDomain 구조로 이루어짐
![alt text](image.png)

DNS 종류
    A	    도메인을 IPv4 주소로 매핑	A → 142.250.190.68
    AAAA	도메인을 IPv6 주소로 매핑	AAAA → 2404:6800:4004:80b::2004
    CNAME	별칭 → 실제 도메인	        www.example.com → example.com
    MX	    메일 서버 정보	            Mail → mail.example.com
    NS	    네임서버 정보	            NS → ns1.example.com
    TXT	    도메인 설명 or 인증 정보	SPF, DKIM 등
    PTR     IP주소를 도메인으로 매핑

DNS 질의 방식
    Recursive Query	- 클라이언트가 “끝까지 찾아달라” 요청 (보통 사용자 → DNS 서버)
    Iterative Query	DNS - 서버가 다른 DNS 서버에게 “너가 알면 말해줘, 몰라도 어디로 가야할지 알려줘” 방식

    만약 google.com을 조회하고 싶다고 함
    => 클라이언트는 리졸빙 캐시에 google.com이 있는지 물어봐. 없으면 리졸빙 캐시가 재귀적으로 루트, TLD, 권한서버에 질의해서 결과를 클라이언트에게 반환함
    

DNS 보안
    DNS Spoofing - 공격자가 가짜 DNS 응답을 만들어 사용
    DNS Cache Poisoning - 캐시에 잘못된 도메인-IP 매핑 저장하도록 유도
    DNS MITM - DNS 요청이 공격자를 거쳐 DNS 서버로 가는 동안 요청 조작
    