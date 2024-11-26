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