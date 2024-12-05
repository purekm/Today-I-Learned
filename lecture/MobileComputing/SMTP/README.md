# SMTP Overview
- 우편 배달과 유사
- 편지를 봉투에 넣음 -> 수신자의 이름과 주소 작성 -> 우체국에 맡김 -> 우체국끼리 전달망을 통해 이송 -> 수신자의 우편함에 전달 -> 수신자가 우편함에서 인출
- rudals4349@hanyang.ac.kr이 있으면, rudals4349는 ID, hanyang.ac.kr은 Domain
- ![alt text](image.png)
- 우선 순위가 높은 곳으로 exchange 될 것

# Email
- 이메일 발송 - 발신자의 Domain을 책임진 MX(메일 서버)에게 발송 요청
- MX의 queue에 들어감
- MX의 queue에서 발송 시, 수신자 이메일의 도메인 이름 추출 후 MX 검색
- 수신 Domain의 MX 서버에 TCP 연결
- SMTP 프로토콜로 발신 MX 와 수신 MX 사이에 메일 전달

- 이메일 수신 - 수신 Domain MX가 수신자의 이메일에 해당 메일을 넣음
- 수신자가 꺼낼 때 까지 메일 존재
- 수신자는 pull 프로토콜을 통해 메일 수신(POP3,IMAP,HTTP)

- ![alt text](image-2.png)

## SMTP

# Main Components
- User Agents(UA): 사용자의 이메일 메시지 준비 지원
- Mail Transfer Agent(MTA): 이메일을 인터넷을 통해 전송하는 역할로, MX에서 MX로 전달
- ![alt text](image-1.png)
- Alice는 UA를 통해 메일 준비 후, MTA client로 메일을 보냄.
- MTA client는 이메일을 spool에 두고 전송 (Qestion: spool에는 저장되는가? 사라지는가?)
- Bob의 MX는 MTA 서버를 통해 메시지를 수신하고, 이를 저장
- Bob은 UA를 통해 MX에 접속하고, 이메일 확인 후 MTA -> UA로 전달

# Command and response
- ![alt text](image-3.png)
- ![alt text](image-4.png)

# Message transfer
- ![alt text](image-5.png)
- 위의 사진은 보안적인 문제가 존재(송신자 및 수신자에 대한 인증X, 암호화X)

- Connection establishment
- ![alt text](image-6.png)
- Connection termination
- ![alt text](image-7.png)

# SMTP 한계
- 메시지를 7it 아스키코드 형식으로 전달
- Authentication 메커니즘이 없음
- 메시지가 암호화되지 않음

# MIME(SMTP extension)
- 아스키 코드가 아닌 데이터를 아스키 코드로 변환하고 client MTA에 전송
- MIME를 통해 다시 원래의 아스키 코드가 아닌 데이터로 변환되서 전송
- ![alt text](image-8.png)

# MIME Header
- ![alt text](image-9.png)