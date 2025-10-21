
---

# Kubernetes Service 정리

## Service란?

Kubernetes의 **Service**는 **Pod 그룹 간 연결을 가능하게 하는 객체**로,
pod와 연결할 때 IP 불안전성(pod 재생성)때문에 사용함

---

## 외부 접근 문제

일반적으로 외부(예: 노트북)에서 직접 Pod에 접근할 수 없다.
Pod는 서로 다른 네트워크에 존재하기 때문이다.

* Pod 간 직접 `ping` 불가능
* SSH를 통해 Node에 접속 후, `curl`로 Pod 접근은 가능하지만 불편함

**SSH 없이** 노트북 → Node → Pod로 접근하고 싶을 때 사용하는 것이 **Kubernetes Service**다.

Service는 **요청을 매핑(mapping)**하여 외부 요청이 적절한 Pod로 전달되도록 한다.

---

## Service Type

Kubernetes에는 여러 가지 **Service Type**이 있다.

| Type         | 설명                       |
| ------------ | ------------------------ |
| ClusterIP    | 클러스터 내부에서만 접근 가능 (기본값)   |
| NodePort     | 외부에서 Node IP + 포트로 접근 가능 |
| LoadBalancer | 외부 로드밸런서와 연동 (Cloud 환경)  |
| ExternalName | DNS 이름을 외부 서비스에 매핑       |

---

## NodePort

NodePort는 **클러스터 외부에서 Pod에 접근할 수 있도록 해주는 서비스 타입**이다.

![NodePort Diagram](image-6.png)

### 구조 요약

| 항목           | 의미                         | 예시    |
| ------------ | -------------------------- | ----- |
| `targetPort` | 실제 Pod의 애플리케이션 포트          | 80    |
| `port`       | Service의 내부 포트 (ClusterIP) | 80    |
| `nodePort`   | 외부에서 접근할 포트 (노드 포트)        | 30008 |

NodePort의 포트 범위는 **30000~32767** 이며,
지정하지 않으면 자동으로 범위 내 임의 포트가 할당된다.

---

### definition 파일 예시

```yaml
apiVersion: v1
kind: Service
metadata:
  name: web-service
spec:
  type: NodePort
  selector:
    app: web
  ports:
    - port: 80
      targetPort: 80
      nodePort: 30008
```

> `selector`는 Pod의 `labels`와 연결되어, Service가 트래픽을 보낼 대상을 찾는다.

---

### Load Balancing

Service는 동일한 label을 가진 여러 Pod 중 하나로 요청을 자동 분배한다.
즉, **기본적으로 LoadBalancer 역할도 수행**한다.

---

### 여러 노드 환경

여러 노드에 Pod가 분산되어 있더라도,
Service를 생성하면 **모든 노드에서 동일한 포트로 접근이 가능**하다.

즉, 다음 세 가지 경우 모두 별도 설정이 필요 없다:

1. Single Node, Single Pod
2. Single Node, Multiple Pods
3. Multiple Nodes, Multiple Pods

---

## ClusterIP

**ClusterIP**는 기본 서비스 타입으로,
**클러스터 내부 통신(예: Frontend ↔ Backend ↔ Redis)**을 위한 **가상의 IP**를 제공한다.

### 정의 파일 예시

```yaml
apiVersion: v1
kind: Service
metadata:
  name: backend-service
spec:
  type: ClusterIP
  selector:
    app: backend
  ports:
    - port: 8080
      targetPort: 8080
```

ClusterIP는 외부에서 접근할 수 없고,
클러스터 내부 Pod 간 통신을 위한 단일 **인터페이스 역할**을 한다.

---

## 요약

| 항목    | NodePort                   | ClusterIP        |
| ----- | -------------------------- | ---------------- |
| 접근 범위 | 외부 접근 가능 (Node IP + Port)  | 내부 접근만 가능        |
| 용도    | 외부 트래픽 유입                  | 내부 서비스 간 통신      |
| 설정 항목 | port, targetPort, nodePort | port, targetPort |
| 로드밸런싱 | Pod 간 부하 분산                | 내부 Pod 간 부하 분산   |
| 기본 여부 | ❌                          | ✅ (기본 타입)        |

---
