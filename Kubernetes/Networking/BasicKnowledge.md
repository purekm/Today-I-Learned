
# 네트워크 기초 정리 (Switching / Routing / DNS / Namespace)

## 1. Switching과 Routing

### 1.1 장비 개념

- **Switch (스위치)**  
  - OSI **L2 (Data Link) 레이어**에서 동작  
  - **MAC 주소** 기반으로 프레임을 전달  
  - **같은 네트워크(같은 브로드캐스트 도메인)** 내에서 트래픽을 전달하기 위한 장비

- **Router (라우터)**  
  - OSI **L3 (Network) 레이어**에서 동작  
  - **IP 주소** 기반으로 패킷을 전달  
  - **서로 다른 네트워크(서브넷)** 사이를 연결하는 장비

---

## 2. 기본 네트워크 명령어

- `ip link`  
  - 네트워크 인터페이스 목록 확인 및 상태 관리
  - 예: `ip link show`, `ip link set eth0 up`

- `ip addr add`  
  - 네트워크 인터페이스에 IP 주소 할당  
  - 예: `ip addr add 192.168.1.10/24 dev eth0`

- `ip addr`  
  - 인터페이스별 IP 정보 확인  
  - 예: `ip addr show`

- `route` / `ip route`  
  - 라우팅 테이블 확인 및 설정
  - 예(신규 방식 권장):  
    - `ip route show`
    - `ip route add 10.0.2.0/24 via 10.0.1.1`

- **gateway**  
  - 다른 네트워크로 나갈 때 사용하는 **기본 라우터의 IP 주소**
  - 예: `ip route add default via 192.168.1.1`

---

## 3. 게이트웨이의 역할

**질문:** 라우터가 물리적으로 연결되어 있어도, 게이트웨이를 설정하지 않으면 다른 네트워크로 보낼 수 없는 이유?

1. 호스트는 **“내가 아는 네트워크(로컬 서브넷)”**가 아니면,
   - 라우팅 테이블에서 **“어디로 보내야 하는지(다음 홉, gateway)”**를 찾는다.
2. 게이트웨이 IP가 라우팅 테이블에 없으면,
   - 어떤 라우터(어느 IP)를 향해 패킷을 보내야 할지 모른다.
3. IP를 모르면 **ARP로 라우터 MAC도 알 수 없음**  
   → L2 레벨(이더넷)에서 프레임을 보낼 대상이 없으니 패킷이 나갈 수 없다.

정리하면:

> **라우터는 있어도, “내가 어느 라우터를 통해 나갈지”를 알려주는 게이트웨이 설정이 없으면 다른 네트워크로 나갈 수 없다.**

---

## 4. Linux 호스트를 라우터로 사용하기

### 4.1 예시 시나리오

- A ↔ B ↔ C
- A와 C는 서로 다른 네트워크에 있고, 둘 다 B와는 각각 연결되어 있다고 하자.
- A에서 C로 통신하려면:
  - A 입장에서는 **C로 가는 경로의 다음 홉이 B**여야 한다.
- C에서 A로 응답을 보낼 때도:
  - C 입장에서는 **A로 가는 경로의 다음 홉이 B**여야 한다.

따라서:

- A의 라우팅 테이블: `dest(C 대역) via B_IP`
- C의 라우팅 테이블: `dest(A 대역) via B_IP`

### 4.2 IP 포워딩 활성화

Linux 호스트가 단순한 클라이언트가 아니라 **라우터 역할**을 하려면, **IP 포워딩 기능**을 켜줘야 한다.

- 일시적으로 활성화:

```bash
echo 1 > /proc/sys/net/ipv4/ip_forward
````

* 영구적으로 활성화 (`/etc/sysctl.conf`):

```ini
net.ipv4.ip_forward = 1
```

적용:

```bash
sudo sysctl -p
```

---

## 5. DNS와 이름 해석

### 5.1 /etc/hosts

* 예: DB 서버 IP가 `192.168.1.11`이고, `db`라는 이름으로 접근하고 싶을 때:

```text
# /etc/hosts
192.168.1.11   db
```

* 이 경우 `ping db`를 하면, **로컬 /etc/hosts를 통해 이름 → IP 변환**이 이루어진다.
* **작은 환경, 테스트용, 임시 매핑**에 자주 사용.

### 5.2 DNS 서버

* 여러 IP/도메인을 체계적으로 관리하려면 **DNS 서버**가 필요하다.
* DNS 서버는 **도메인 네임 ↔ IP 주소** 변환을 제공.
* 클라이언트는 `/etc/resolv.conf`에 DNS 서버를 적어둔다:

```text
# /etc/resolv.conf
nameserver 8.8.8.8
nameserver 1.1.1.1
```

### 5.3 /etc/hosts와 DNS의 우선순위

* 일반적인 Linux 기본 설정(nsswitch 기준):

```text
# /etc/nsswitch.conf 의 일부
hosts:      files dns
```

* 의미:

  1. 먼저 **/etc/hosts (files)** 를 확인
  2. 없으면 **DNS** 조회

따라서:

* 동일한 이름이 `/etc/hosts`와 DNS에 모두 존재하고 IP가 다르면

  * 기본 설정에서는 `/etc/hosts`가 우선 → `/etc/hosts`의 IP가 사용된다.
* `/etc/nsswitch.conf`에서 `hosts:` 항목을 수정하면 우선순위를 바꿀 수 있다.

  * 예: `hosts: dns files` 로 바꾸면 DNS를 먼저 본다.

---

## 6. Network Namespace & Container 네트워크

### 6.1 컨테이너와 네임스페이스

* 컨테이너가 생성되면, 보통 **해당 컨테이너용 network namespace**가 생성된다.
* 각 네임스페이스는:

  * **자신만의 인터페이스 목록**
  * **자신만의 라우팅 테이블**
  * **자신만의 iptables 규칙**
    등을 가진다.

> Kubernetes Pod는 여러 컨테이너가 **하나의 network namespace를 공유**한다는 점도 함께 기억해두기.

### 6.2 네임스페이스별 인터페이스 확인

* 전체 네임스페이스 목록:
  `ip netns list`
* 특정 네임스페이스 내 인터페이스 확인:

```bash
ip netns exec <ns이름> ip link
# 또는
ip -n <ns이름> link
```

* 단순 현재 네임스페이스(호스트)의 인터페이스 확인:
  `ip link`

* 개념:

  * **호스트**(root 네임스페이스)는 관리자로서 모든 네임스페이스의 리소스를 볼 수 있다.
  * 네임스페이스 안에서는 **자기 네임스페이스 내부의 리소스만 보인다** → 격리 효과.

---

## 7. 네임스페이스 간 연결 (veth)

### 7.1 veth (virtual ethernet) 페어

서로 다른 네트워크 네임스페이스를 **케이블처럼 연결**할 때 사용하는 것이 veth 인터페이스.

1. **veth 페어 생성**

```bash
ip link add veth-red type veth peer name veth-blue
```

2. **각 인터페이스를 네임스페이스에 할당**

```bash
ip link set veth-red netns red
ip link set veth-blue netns blue
```

3. **각 네임스페이스 안에서 IP 주소 할당**

```bash
ip -n red  addr add 192.168.10.1/24 dev veth-red
ip -n blue addr add 192.168.10.2/24 dev veth-blue
```

* `dev` 키워드는 **어느 인터페이스에(IP를) 설정하는지** 지정할 때 사용.

4. **인터페이스 활성화**

```bash
ip -n red  link set veth-red up
ip -n blue link set veth-blue up
```

이제 `red` 네임스페이스에서 `ping 192.168.10.2` 하면 `blue` 네임스페이스까지 통신된다.

---

## 8. 여러 네임스페이스를 스위치처럼 연결하기 (Linux Bridge)

veth 페어로 1:1 연결만 하면 **네임스페이스가 많을 때 비효율적**이다.
여러 네임스페이스를 한 곳에 모으려면 **가상 스위치(브리지)**를 사용한다.

### 8.1 Linux Bridge 생성

1. **브리지 인터페이스 생성**

```bash
ip link add v-net-0 type bridge
```

2. **브리지 인터페이스 활성화**

```bash
ip link set v-net-0 up
```

3. 각 네임스페이스에 veth를 하나씩 만들고 **브리지에 연결된 쪽을 호스트에 둔다**:

```bash
# 예시: red 네임스페이스에 연결할 veth 쌍
ip link add veth-red type veth peer name veth-red-br
ip link set veth-red netns red

# 브리지에 호스트 쪽 인터페이스 붙이기
ip link set veth-red-br master v-net-0
ip link set veth-red-br up
```

이 과정을 blue, green 등 다른 네임스페이스에도 반복하면
`v-net-0`이 **가상의 스위치 역할**을 하게 된다.

---

## 9. NAT (프라이빗 네트워크 → 외부)

프라이빗 IP 대역(예: 10.x, 192.168.x, 172.16~31.x)이 외부 인터넷과 통신하려면 **NAT**가 필요하다.
Linux에서는 보통 `iptables`를 사용해 설정한다.

### 9.1 간단한 SNAT/MASQUERADE 설정

```bash
# 예: 10.0.0.0/24 대역이 eth0를 통해 인터넷에 나가도록 설정
iptables -t nat -A POSTROUTING \
  -s 10.0.0.0/24 \
  -o eth0 \
  -j MASQUERADE
```

* `-t nat` : NAT 테이블 사용
* `POSTROUTING` : 패킷이 나가기 직전 단계에서 주소를 바꾼다
* `-s` : 소스 IP 대역 (프라이빗 네트워크)
* `-o` : 외부로 나가는 인터페이스 (예: eth0)
* `-j MASQUERADE` : 외부 인터페이스의 IP로 소스 IP를 변환(NAT)

---

## 10. 주요 디렉터리 역할

* `/etc`

  * 시스템 및 각종 서비스의 **설정 파일**들이 위치
  * 예: `/etc/hosts`, `/etc/resolv.conf`, `/etc/sysctl.conf`, `/etc/nsswitch.conf`, …

* `/var`

  * **변하는 데이터**가 저장되는 디렉터리
  * 로그, 큐, 캐시, 임시 데이터 등

* `/var/log`

  * 시스템 및 서비스 **로그 파일** 위치
  * 예: `/var/log/syslog`, `/var/log/messages`, …

* `/var/lib`

  * 서비스의 **상태/데이터**가 저장되는 곳
  * 예: `/var/lib/etcd`, `/var/lib/docker`, `/var/lib/mysql` 등


