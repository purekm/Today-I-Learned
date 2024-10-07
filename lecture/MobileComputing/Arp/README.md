## ARP
- IP 주소만으로는 데이터 전송이 불가하므로, Mac Address를 찾아야함
- Mac address는 ARP(Broadcast)를 통해서 찾음
- Dynamic은 response를 받고, static은 인위적으로 table에 넣은 type
- **Directed broadcast**는 특정 네트워크의 모든 호스트에게 패킷을 전송하는 방식으로, IP 주소는 특정 네트워크의 네트워크 주소에 해당하는 서브넷에서 마지막 주소를 사용하여 마지막에 255를 사용
- 모든 노드는 ARP 테이블을 가지고 있음
- ARP는 1-hop 단위로 이동하기 때문에, 같은 서브넷에 있는 노드들의 mac주소가 중요

## G-ARP 
- 자기 자신의 IP를 broadcast
- **중복된 address**가 있는지 확인해보기 위해서 G-ARP 사영
- ![alt text](image.png)
- 2-2의 경우에는 일단 ARP table을 업데이트 해줘야 함
- MAC address가 바뀌었다면, G-ARP를 통해 자기 자신의 IP를 알려줌
- 2-3의 경우에는 A는 이미 B에게 ARP request를 받은 이후의 상황이기 때문에 B의 MAC-IP가 없는게 신뢰가 없으므로 응답을 거부함
- ![alt text](image-1.png)
- 2번으로 인해 IP가 변경된 줄 알고, ARP 테이블을 갱신
- 3번에서는 response를 A에게 보냄
- 4번에서는 Hijacking을 당해서, B와 D는 C에게 보내도 A로 전송됨
- **G-ARP** 는 **DAD(Duplicate Address Detection**을 하지 못함

- ARP Poisoning, Spoofing 을 방지하려면, 라우터가 주기적으로 ARP request를 반복하여 A,C가 모두 응답하게 함
- 라우터는 A와 C에게 번갈아가면서 보내게 되는데, 결국 C가 피해를 받음

## ACD
- address conflict detection
- DAD를 방지하기 위해 source ip를 0.0.0.0 으로 설정 -> ARP probe
- Source IP를 0.0.0.0으로 설정하고 보냈을 때, 응답이 있으면 충돌 없으면 ARP

## Proxy ARP
- source에서 destination IP를 적어서 데이터를 보낼 때, 같은 subnet에 없으면 라우터가 자신의 MAC주소를 매핑하여 response

## Directed ARP
- unicast로 요청

