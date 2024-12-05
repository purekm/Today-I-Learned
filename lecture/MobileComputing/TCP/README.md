## TCP
# Challenges
- drop packets
- delay packets
- deliver packets out of order
- replicate pacakets
- corrupt packets

# Service
- Reliable delivery
- - IP가 packet을 읽어버리는 경우
- In-order delivery
- - IP가 순서 잘못보내주면, TCP가 reordering한 후 application에게 전달
- Flow Control
- - 수신 application이 받을 수 있는 만큼만 배달
- Byte-stream
- - 데이터는 bytes의 연속
- Connection oriented
- - 데이터 전송관리
- - ![alt text](image.png)
- - connection 생성 후 data transfer

# Reliable Delivery
- Checksum
- Sequence numbers
- Retransmission
- - retransmit lost or corrupted data
- - Timeout based
- - Fast retransmit 

# TCP Header
- ![alt text](image-1.png)
- Sequnce number은 Starting number of data(byte offset)
- Ack는 "What's next?"
- HdrlLen = 5 : if no options
- Must Be Zero 6bits
- Window Size를 통해서 flow controll
- ![alt text](image-3.png)
- 총 20bytes

# ISN
- Initial Sequence Number은 TCP 연결에서 처음 전송되는 Number
- ISN은 계속 변해야 함

# Establishing a TCP Connect
- ![alt text](image-2.png)
- ![alt text](image-4.png)

# SYN Packet을 잃어버렸을 경우
- Server discards the packet
- Sender set timer and waits SYN-ACK(and retransmit)
- timer's default time : 3seconds, other use 6seconds

# Connection Termination
- X sends FIN to Y (active close)
- Y ACKs the FIN
- and Y sends a FIN to X (passive close)
- X Acks the FIN
- ![alt text](image-5.png)
- 마지막까지 끝내면 완전히 closed
- 만약 마지막 ACK가 timeout이 되면, B는 FIN을 다시 보냄
- 모든 바이트가 ACK 응답을 받기 전에 FIN을 보낼 순 있지만, FIN이 ACK되기 전에는 연결 종료를 할 수 없음

# Abrupt Termination
- ![alt text](image-6.png)
- A가 B에게 RST를 보냄으로써 비정상적인 연결을 종료하고 싶음
- RST는 ack를 기다리지 않음
- RST를 보낸 이후, 전송중인 데이터는 손실되고 추가 전송시 추가 RST 발생

# Situation
- ![alt text](image-7.png)

# SACK
- TCP 세그먼트 한번에 여러 개 보낼 때 중간에 잃어버린 것만 알려줌(SLE,SRE)
- TCP 성능 향상