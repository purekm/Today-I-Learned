## Layering
- **Protocol**은 end users가 연락할 수 있도록 하는 rule으로, 여러 기기들이 상호 운용 가능하도록 만드는 것이 주 목적.
- **Layer**을 나누는 이유는 복잡성을 줄이고 각 계층이 독립적으로 기능을 수행하도록 하기 위함. 각 계층은 서로 다른 작업을 수행하며, 다른 계층의 정보를 직접적으로 간섭할 수 없도록 설계되어있음. 예를 들어, 라우터는 network layer 까지만 데이터를 확인하고 처리함.

## Interface 
- **interface** 는 네트워크에서 통신을 가능하게 하는 장치 또는 소프트웨어 구성 요소.
OS에서는 기본적으로 여러 interface에 대한 protocol rules 을 가지고 있음. interface(Ethernet에서 접속하는 protocol과 wifi protocol)가 다르니까 그걸 OS가 조절 

Layer5~Layer3까지는 다른 게 없고 Link layer에서부터 다른 interface로 인한 차이 발생.

## Layered Communications
- 실제로는 아래의 layer을 통해서 연락하지만, 상대방 입장에서는 같은 layer와 연락하는 느낌을 줌

## PDU와 Demultiplexing
- **PDU**는 해당 layer에서 보내는 실질적인 메시지로, 각 계층에서 주고받는 데이터의 단위를 뜻함.
- **Demultiplexing** 은 수신된 데이터에서 각 계층의 헤더를 분석하고, 해당 계층의 프로토콜에 따라 데이터를 사위 계층으로 전달하는 과정. 각 계층의 헤더에는 어떤 프로토콜을 사용할지 명시된 필드가 있어서, 이를 통해 데이터가 적절하게 처리됨.

