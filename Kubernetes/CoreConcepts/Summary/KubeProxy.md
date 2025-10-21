# Pod Network & Kube-Proxy

Kubernetes에서는 Pod 간 통신을 위해 **Pod Network**라는 내부 가상 네트워크를 사용합니다.  
이를 통해 **다른 Worker Node의 Pod들과도 자유롭게 통신**할 수 있습니다.

---

## Pod Network

- 모든 Pod에는 고유한 IP가 할당되며, Pod 간에는 NAT 없이 직접 통신 가능
- Pod Network는 클러스터 내부의 통신을 위한 **논리적 네트워크**

---

## 서비스를 통한 통신

- 웹 애플리케이션이 DB에 접근할 때 **직접 Pod IP로 접근하는 것보다 Service를 사용하는 것이 안전하고 안정적**
- Service에는 **고정된 클러스터 IP**가 할당되므로, 내부 통신 시 IP로 접근 가능

---

## Kube-Proxy

- 클러스터의 각 노드에서 실행되는 프로세스
- 새로운 서비스를 감지하고, 트래픽을 적절한 Pod로 라우팅
- **iptables rule**을 사용하여 서비스에 도달하는 요청을 적절한 백엔드 Pod로 전달

Service는 pod 그룹에 대한 추상적 접근점 제공, DNS 이름 제공
kube-proxy는 Service로 넘어온 트래픽을 실제 pod로 전달


