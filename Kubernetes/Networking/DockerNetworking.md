
# Kubernetes 네트워크 정리 (Docker 네트워크 ~ Gateway API)

## 1. Docker / 컨테이너 네트워크 모드

### 1.1 Docker의 기본 네트워크 모드

- **none network**
  - 컨테이너에 네트워크 인터페이스(IP)가 거의 없는 상태
  - 외부 통신 X (필요시 직접 네트워크 설정을 붙여줘야 함)

- **host network**
  - 컨테이너가 **호스트의 네트워크 네임스페이스를 그대로 사용**
  - 컨테이너와 호스트의 IP/포트 공간이 같음 (격리 X)
  - 예: 컨테이너에서 80 포트를 열면, 호스트의 80 포트가 열린 것과 같음

- **bridge network**
  - 호스트에 **가상 브릿지 인터페이스(docker0 등)** 생성
  - 컨테이너마다 veth 인터페이스를 생성해서 이 브릿지에 연결
  - 컨테이너끼리는 브리지 네트워크 안에서 통신 가능
  - 기본적으로 Docker 설치 시 `bridge` 네트워크(`docker0`)가 생성됨

---

## 2. CNI (Container Network Interface)

### 2.1 CNI란?

- 다양한 컨테이너 런타임 (Docker, containerd, CRI-O 등)에서  
  **네트워크 설정을 통일된 방식으로 처리하기 위한 표준 인터페이스**
- “프로그램(런타임)이 **Pod/컨테이너를 만들 때** 네트워크를 어떻게 붙여달라고 CNI 플러그인을 호출하는지”를 규정

Kubernetes 자체는 **“Pod 네트워크를 이렇게 제공해야 한다”는 모델/요구사항만 정의**하고,  
실제 **네트워크 인터페이스 생성/삭제, 라우팅 설정**은 CNI 플러그인에게 맡긴다.

### 2.2 CNI 플러그인이 하는 일

Pod가 생성될 때:

- Pod용 네트워크 네임스페이스 생성
- Pod 안에 veth 인터페이스 생성
- Pod에 **IP 주소 할당**
- Pod의 인터페이스를 **호스트의 브릿지(예: cni0)** 등과 연결
- 라우팅/NAT 등의 규칙 설정

Pod가 삭제될 때:

- Pod 네임스페이스/인터페이스 제거
- 관련된 라우팅/NAT 규칙 정리

### 2.3 CNI 관련 경로

- **플러그인 바이너리 위치**
  - `/opt/cni/bin`
  - 예: `bridge`, `host-local`, `loopback`, `calico`, `weave` 등 실행 파일

- **CNI 설정 파일 위치**
  - `/etc/cni/net.d/`
  - 예: `10-weave.conflist`, `10-flannel.conflist` 등

---

## 3. Cluster Network와 포트

### 3.1 Control Plane (Master Node) 포트

- `kube-apiserver`: **6443**
- `kube-scheduler`: **10259**
- `kube-controller-manager`: **10257**
- `etcd`:
  - **2379**: 클라이언트( kube-apiserver, etcdctl 등 )가 접속하는 포트
  - **2380**: etcd **클러스터 노드 간 통신**용 포트 (peer 통신)

실제로 `netstat -nltp`로 보면 2379 포트에 더 많은 연결이 걸려 있는 것을 볼 수 있다.

### 3.2 Worker Node 및 공통 포트

- `NodePort` 서비스: **30000–32767** 범위  
  (외부에서 접근 가능하도록 노드에 열리는 포트 범위)
- `kubelet`: **10250**  
  (API 서버가 각 노드의 kubelet과 통신할 때 사용)

---

## 4. containerd와 브리지 인터페이스

- Docker는 기본적으로 `docker0` 브리지 인터페이스를 생성.
- **containerd** 자체는 Docker처럼 자동으로 브리지를 만들지 않고,  
  **CNI 플러그인 설정에 따라** 브리지 인터페이스가 생성된다.
  - 예: 기본 CNI bridge 플러그인을 쓰면 `cni0` 같은 이름의 브리지가 생김.
- 따라서 “containerd의 브리지 이름”은 보통 `cni0`이지만,  
  실제 이름은 CNI 설정 파일(/etc/cni/net.d)에 따라 달라질 수 있다.

---

## 5. Weave CNI 동작 방식 (예시)

Pod 간 통신 흐름 (Weave Net 기준):

1. **Pod → 브리지**
   - Pod의 veth 인터페이스를 통해 호스트의 브리지(예: `weave` 브릿지)로 패킷 전달.
2. **브리지 → Weave 에이전트**
   - 호스트에서 실행 중인 Weave 에이전트(데몬셋 Pod)가 패킷을 가로채거나 처리.
3. **캡슐화 (Encapsulation)**
   - 원래 패킷의 src/dst가 **Pod IP** 기반인데,
   - 이 패킷을 **노드 IP 기반 패킷 안에 싸서(터널링)** 다른 노드의 Weave 에이전트에게 전달.
4. **다른 노드의 Weave 에이전트 → 대상 Pod**
   - 도착 노드의 Weave 에이전트가 패킷을 디캡슐화(Encap 해제) 하고,
   - 해당 노드의 브리지/Pod로 다시 전달.

캡슐화 이유:

> “Pod IP끼리 직접 통신하는 것처럼 보이게 만들기 위해,  
> 실제로는 노드 IP 사이에 터널을 만들고 그 안에 Pod 트래픽을 태운다.”

---

## 6. CNI 제거 (Lab)

어떤 CNI를 제거할 때 일반적인 절차:

1. **DaemonSet 삭제** (CNI 에이전트 Pod)
2. **ConfigMap 삭제** (CNI 설정)
3. `/etc/cni/net.d/` 안의 CNI 설정 파일 삭제

하나의 YAML(manifest)로 설치했다면:

```bash
kubectl delete -f <cni-yaml-file>.yaml
````

로 한번에 삭제 가능.

---

## 7. Service Networking

### 7.1 Service 타입 요약

* **ClusterIP**

  * 기본 타입
  * **클러스터 내부**에서 Pod에 접근할 때 사용
  * `10.x.x.x` 대역의 가상 IP가 부여됨

* **NodePort**

  * 외부에서 `NodeIP:NodePort`로 접근 가능
  * 내부에서는 여전히 **ClusterIP:port** 또는 **서비스 DNS 이름**을 사용

* **LoadBalancer**

  * 클라우드 환경(CSP)에서 **외부 로드밸런서**를 자동 생성
  * 외부 IP를 부여하고, 내부적으로는 NodePort/ClusterIP로 연결

### 7.2 Service 가상 IP와 라우팅

“Service는 가상의 IP인데, 어떻게 동작하나?”

1. Service가 생성되면, **Service CIDR 범위**에서 IP를 하나 할당.
2. `kube-proxy`가 각 노드에 **포워딩 규칙(iptables/ipvs)**를 설정:

   * `ServiceIP:Port`로 들어온 트래픽을
   * 해당 Service의 **Endpoint(Pod IP:targetPort)** 중 하나로 라우팅 (로드밸런싱)

### 7.3 NodePort의 3가지 포트

NodePort 타입 Service 예:

* `port`:

  * **서비스 내부 포트(ClusterIP 기준)**
  * 클러스터 내부에서 `서비스이름:port`로 접속할 때 사용하는 포트
* `targetPort`:

  * 실제 **컨테이너(Pod)가 listen 하는 포트**
* `nodePort`:

  * 클러스터 외부에서 `NodeIP:nodePort`로 접속할 수 있는 포트
  * 기본 포트 범위: **30000–32767**

#### NodePort 접근 구조

* 외부 → `NodeIP:nodePort`

  * Node에서 kube-proxy 규칙에 의해 Service → Pod들로 전달
* 내부 → 일반적으로 `서비스이름:port` 또는 `ClusterIP:port` 사용

#### 왜 NodePort가 불편한가?

* NodePort는 보통 **고정된 높은 포트 번호**를 사용해야 한다.
* 실제 서비스에서는:

  * DNS로 도메인 이름을 **외부 로드밸런서나 리버스 프록시 IP**에 매핑
  * 그 프록시가 내부적으로 `NodeIP:nodePort`로 트래픽을 전달하거나,
  * 혹은 CSP의 LoadBalancer가 NodePort에 연결해준다.
* 즉, “일반적인 80/443 포트 사용”은 보통 **외부 LB/프록시에서 해결**하는 문제.

---

## 8. Ingress

### 8.1 Ingress 개념

* **Ingress Controller**

  * Ingress 리소스를 읽고,
  * 실제로 HTTP/HTTPS 트래픽을 **Service로 라우팅**해주는 프로그램
  * 예: NGINX Ingress Controller, HAProxy, Traefik 등
  * 기본적으로는 없다. 보통 **Deployment + Service** 형태로 직접 설치해야 함.
  * 부가적으로 ConfigMap, ServiceAccount, Role, RoleBinding 등이 필요.

* **Ingress Resource**

  * “어떤 도메인의 어떤 경로 → 어떤 Service”로 라우팅할지 정의한 **설정(YAML)**
  * 여러 **host**, 여러 **path**, 다양한 백엔드 Service를 매핑 가능

### 8.2 Ingress 생성 (명령형 예시, 1.20+)

```bash
kubectl create ingress my-ingress \
  --rule="app.example.com/app=app-service:80"
```

* 실제로는 YAML로 선언형 관리하는 것이 일반적.

### 8.3 Ingress와 LoadBalancer

* 클러스터 외부에서는 보통 **LoadBalancer 타입 Service**가 Ingress Controller 앞에 붙는다.
* 흐름:

  * 외부 → [CSP LoadBalancer] → [Ingress Controller Pod(Service)] → [각 백엔드 Service/Pod]
* Kubernetes의 **Service 자체도 로드밸런싱 기능**을 제공하지만,

  * Ingress는 주로 **HTTP/HTTPS 레벨의 라우팅/가상 호스트/경로 기반 라우팅**에 초점.

### 8.4 Ingress default backend와 rewrite

* Ingress 규칙에 **어떤 path/host에도 매칭되지 않으면** → `defaultBackend`로 라우팅.

  * `defaultBackend`가 무엇인지 확인하려면 Ingress 리소스의 `defaultBackend` 필드나
  * 컨트롤러 설정(예: NGINX Ingress의 default backend)을 확인.

* NGINX Ingress 예:

  * `nginx.ingress.kubernetes.io/rewrite-target: /`
    같은 **annotation**을 사용하면,
    `/app`으로 온 요청을 **백엔드에는 `/` 경로로 전달**하게 할 수 있다.
  * 백엔드 애플리케이션이 기대하는 URL 구조가 다를 때 유용.

---

## 9. kube-proxy 모드

kube-proxy는 Service를 Pod로 라우팅하기 위한 **포워딩 규칙**을 각 노드에 설정한다.

* **userspace 모드** (아주 예전, 거의 사용 X)
* **iptables 모드** (기본, 가장 널리 사용)
* **ipvs 모드**

  * 대규모 환경에서 더 나은 성능/기능 제공

현재 모드를 확인하려면:

* `kube-proxy`가 사용하는 **ConfigMap** 확인
  (예: `kube-system` 네임스페이스의 `kube-proxy` ConfigMap)
* `mode`가 비어있으면 기본값인 **iptables** 사용

---

## 10. Kubernetes DNS (CoreDNS)

### 10.1 기본 FQDN 규칙

* Service 접근:

  * `servicename.namespace.svc.cluster.local`

* Pod DNS (kube-dns/coredns가 사용하는 규칙 예시):

  * Pod IP: `10.244.2.5`
  * DNS 이름: `10-244-2-5.namespace.pod.cluster.local`
    (구체적인 도메인 suffix는 클러스터 설정에 따라 달라질 수 있음)

### 10.2 CoreDNS

* CoreDNS는 보통 **2개의 Pod**로 배포되어 가용성을 확보.

* CoreDNS 설정 파일:

  * 컨테이너 내부 경로: `/etc/coredns/Corefile`
  * 실제로는 **ConfigMap** 오브젝트(예: `kube-system/coredns`)로 관리되고,
    이 ConfigMap이 Pod에 마운트된다.

* Pod 내부 `/etc/resolv.conf`:

  * 어떤 DNS 서버를 사용할지 정의
  * 보통 클러스터 DNS 서비스 IP를 가리킴(예: `10.96.0.10`)

---

## 11. API Gateway: Gateway API (Gateway / HTTPRoute)

기존 Ingress의 한계:

* 하나의 Ingress YAML에 여러 팀의 라우팅 규칙을 다 넣어야 하는 경우 등 관리가 복잡
* namespace 단위 격리/권한 관리(RBAC)가 애매함
* 기능 확장 시 컨트롤러 별 annotation에 의존

### 11.1 Gateway API 리소스

1. **GatewayClass**

   * “어떤 종류의 게이트웨이를 쓸지” 정의
   * 예: NGINX Gateway Controller

   ```yaml
   apiVersion: gateway.networking.k8s.io/v1
   kind: GatewayClass
   metadata:
     name: nginx
   spec:
     controllerName: nginx.org/gateway-controller
   ```

2. **Gateway**

   * 실제 **입구 인스턴스**
   * 어떤 포트(80, 443 등), 어떤 프로토콜(HTTP, HTTPS, TCP 등)을 받을지
   * 어떤 Route(HTTPRoute 등)를 허용할지

   ```yaml
   apiVersion: gateway.networking.k8s.io/v1
   kind: Gateway
   metadata:
     name: nginx-gateway
     namespace: default
   spec:
     gatewayClassName: nginx
     listeners:
     - name: http
       protocol: HTTP
       port: 80
       allowedRoutes:
         namespaces:
           from: All
   ```

3. **HTTPRoute**

   * “어떤 요청(호스트/경로/헤더 등)을 어떤 Service로 보낼지” 정의

   ```yaml
   apiVersion: gateway.networking.k8s.io/v1
   kind: HTTPRoute
   metadata:
     name: basic-route
     namespace: default
   spec:
     parentRefs:
     - name: nginx-gateway
     rules:
     - matches:
       - path:
           type: PathPrefix
           value: /app
       backendRefs:
       - name: my-app
         port: 80
   ```

### 11.2 HTTPRoute 예시: HTTP → HTTPS 리다이렉트

```yaml
apiVersion: gateway.networking.k8s.io/v1
kind: HTTPRoute
metadata:
  name: https-redirect
spec:
  parentRefs:
  - name: nginx-gateway
  rules:
  - filters:
    - type: RequestRedirect
      requestRedirect:
        scheme: https
```

HTTPRoute를 통해:

* 리다이렉트(HTTP → HTTPS)
* 경로 rewrite
* 헤더 추가/수정
* 트래픽 분할(가중치 기반 라우팅)
* 요청 미러링
* TLS 설정
* gRPC, TCP/UDP 등 다양한 L4/L7 시나리오

를 보다 **구조화된 방식으로** 표현할 수 있다.

> 정리:
> Gateway + HTTPRoute 조합이 **Ingress + Ingress Controller**와 비슷한 역할을 하지만,
> 더 세분화된 리소스 구조와 표준화된 스펙을 제공한다.

Ingress는 컨트롤러 별 annotation 의존도가 높지만,
Gateway API는 **공통 스펙**을 제공하므로 여러 컨트롤러 간 호환성이 더 좋다
(단, 모든 컨트롤러가 모든 기능을 100% 구현하는 것은 아님).

---

## 12. Kustomize와 Gateway Controller 설치 예

### 12.1 kustomize 기본 이해

* `kubectl kustomize <경로>`:

  * 해당 디렉터리의 kustomization 설정을 읽어서
  * 최종적으로 **병합/패치된 YAML을 stdout으로 출력**
* 보통:

```bash
kubectl kustomize <경로> | kubectl apply -f -
```

형태로 많이 사용 (빌드 결과를 즉시 적용).

### 12.2 Gateway Controller 설치 단계 예 (NGINX Gateway Fabric)

1. **Gateway API CRD 설치** (공용 리소스: GatewayClass, Gateway, HTTPRoute 등)

   ```bash
   kubectl kustomize \
     "https://github.com/nginx/nginx-gateway-fabric/config/crd/gateway-api/standard?ref=v1.5.1" \
     | kubectl apply -f -
   ```

2. **NGINX 전용 CRD 설치 (확장 기능)**

   ```bash
   kubectl apply -f \
     https://raw.githubusercontent.com/nginx/nginx-gateway-fabric/v1.6.1/deploy/crds.yaml
   ```

3. **NGINX Gateway Controller 배포 (NodePort 예)**

   ```bash
   kubectl apply -f \
     https://raw.githubusercontent.com/nginx/nginx-gateway-fabric/v1.6.1/deploy/nodeport/deploy.yaml
   ```

이후, GatewayClass / Gateway / HTTPRoute를 정의해서 실제 트래픽 라우팅을 구성한다.
