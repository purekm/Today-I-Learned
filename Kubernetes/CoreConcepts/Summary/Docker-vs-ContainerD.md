
---

# 🔌 Container Runtime Interface (CRI)

## 1. CRI란?

* **Kubernetes가 다양한 컨테이너 런타임과 연동하기 위해 만든 표준 인터페이스**
* Kubelet이 컨테이너 생성, 시작, 삭제 등을 런타임에 요청할 수 있게 함
* Docker 외에도 여러 런타임(`containerd`, `CRI-O`, 등)을 지원
* 모든 런타임은 **OCI(Open Container Initiative)** 사양을 **준수해야 함**

---

## 2. Open Container Initiative (OCI)

컨테이너 생태계를 위한 표준 사양을 정의하는 프로젝트로, 다음 두 가지 주요 스펙을 포함함:

| 사양             | 설명                                 |
| -------------- | ---------------------------------- |
| `image-spec`   | 컨테이너 이미지를 **어떻게 구성하고 저장**할지에 대한 정의 |
| `runtime-spec` | 컨테이너를 **어떻게 실행해야 하는지**에 대한 정의      |

> ✅ OCI를 준수하면 다양한 런타임 간 **호환성 보장** 가능

---

## 3. Docker와 CRI의 관계

* **Docker는 CRI를 네이티브로 지원하지 않음**
* 이를 보완하기 위해 Kubernetes는 **dockershim**이라는 중간 계층을 만들어 kubelet과 Docker를 연결
* 그러나 **dockershim은 공식적으로 Kubernetes 1.20에서 deprecated**, 1.24부터 **완전히 제거됨**
* 이후에는 `containerd`나 `CRI-O` 같은 **CRI 호환 런타임** 사용 권장

---

## 4. Containerd란?

* **Docker의 핵심 런타임 구성 요소**를 따로 분리한 경량 런타임
* Docker의 불필요한 기능 없이, **컨테이너 실행만을 위한 목적**으로 사용 가능
* Kubernetes에서 **CRI를 통해 직접 사용 가능**

### 주요 도구

| 도구        | 설명                                                               |
| --------- | ---------------------------------------------------------------- |
| `ctr`     | containerd의 네이티브 CLI. 강력하지만 CLI가 불편하고 복잡                         |
| `nerdctl` | Docker CLI와 유사한 UX 제공. containerd 기반으로 설계됨. 대부분 Docker 명령어 호환 가능 |

> ✅ `nerdctl`은 containerd의 기능을 쉽게 사용할 수 있는 CLI로 **실제 개발/운영 환경에서도 자주 사용됨**

---

## 5. CRI의 역할 정리

| 항목        | 설명                                         |
| --------- | ------------------------------------------ |
| 목적        | Kubernetes에서 다양한 컨테이너 런타임과 연동              |
| 구성 주체     | `kubelet` ↔ `container runtime` 사이 통신      |
| 주요 기능     | 컨테이너 **생성, 시작, 중지, 삭제, 상태 확인 등**           |
| 주 용도      | **생산 환경 운영**에 필요한 기본 컨테이너 오케스트레이션          |
| 디버깅 용도 아님 | CRI 자체는 디버깅용이 아니라 **컨테이너 실행을 위한 핵심 인터페이스** |

Kubernetes는 더이상 Docker를 지원하지 않고, Containerd를 기본 런타임으로 사용함
---