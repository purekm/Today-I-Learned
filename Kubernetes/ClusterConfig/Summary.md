# Kubernetes 핵심 개념 및 도구 정리

## 1. 고가용성 (High Availability) 및 etcd
Master Node와 etcd가 여러 개 구성되어 있을 때, 쓰기 요청 시 데이터 일관성이 깨지는 것을 방지하기 위해 **리더(Leader)를 선출하여 리더만 쓰기를 수행**하도록 합니다.

* **쿼럼 (Quorum):** 클러스터가 정상 작동하기 위해 필요한 **과반수의 노드 개수**
    * 과반수를 충족해야 하므로 노드 1개 또는 2개 구성은 의미가 없으며, **최소 3개**가 필요합니다.
    * **결론:** 리더 1명이 쓰기를 담당하고, 쿼럼 수 이상의 노드가 살아있어야 정상적인 클러스터로 동작합니다.

---

## 2. kubeadm을 이용한 클러스터 구성 단계
정석에 맞게 클러스터를 쉽게 구성하기 위해 `kubeadm`을 사용합니다.

1. 클러스터 구성을 위해 프로비저닝된 여러 시스템 또는 VM 준비
2. 역할을 분리하여 한 노드를 **Master Node**, 다른 노드들을 **Worker Node**로 설정
3. 각 노드에 **컨테이너 런타임** 설치
4. 각 노드에 **kubeadm** 설치
5. Master Node에서 초기화 진행 (`kubeadm init`)
6. Master Node와 Worker Node 간 **Pod 네트워크 설정**
7. Worker Node를 클러스터에 조인 (`kubeadm join`)

---

## 3. Helm (Kubernetes 패키지 매니저)
앱 구동에 필요한 컴포넌트들을 한꺼번에 설치, 업그레이드, 삭제할 수 있도록 도와주는 패키지 매니저입니다.

### Helm 3의 주요 특징
* Tiller 컴포넌트가 사라져 클라이언트-서버 구조가 아님
* **3-way strategy 사용:** Helm 2에서는 `kubectl`로 직접 수정한 내역이 리비전에 반영되지 않았으나, Helm 3에서는 Live 리소스를 직접 읽어와 반영함

### 주요 구성 요소 (Components)
* **CLI:** Helm 명령어 도구
* **Chart:** 쿠버네티스 리소스를 만들기 위해 알아야 하는 모든 지침이 포함된 파일 모음
    * `Chart.yaml`: 차트에 대한 메타데이터 (Helm 2는 `apiVersion: v1`, Helm 3는 `apiVersion: v2`)
    * `values.yaml`: 차트에 적용할 기본값 설정 파일
* **Release:** Chart가 클러스터에 설치된 인스턴스. 하나의 릴리스 내에 여러 리비전을 가질 수 있음. (설치 시 릴리스 이름으로 독립적인 추적이 가능하므로 지정하는 것이 좋음)
* **Metadata:** 차트에 대한 정보로, 쿠버네티스 시크릿(Secret)으로 저장됨
* **Repository:** 차트가 저장된 공간 (공식 저장소: [https://artifacthub.io/](https://artifacthub.io/))

### 템플리팅 (Templating)
* YAML 파일을 만들 때 외부 파일의 값을 동적으로 참조하는 방법
* `values.yaml` 파일에 값을 정의해두고, 템플릿 파일에서 `{{ .Values.키이름 }}` 형태로 참조

### 주요 명령어
```bash
# 환경 변수 수정 및 차트 설치
helm install <릴리스이름> <레포지토리/차트이름> --set <변수이름>=<값>

# 레포지토리(Repo) 관리
helm repo add <이름> <URL>  # 레포 추가
helm repo update           # 레포 업데이트
helm repo list             # 레포 목록 확인

# 차트 검색 및 다운로드
helm search repo <검색어>
helm pull <차트이름> --untar  # 압축을 해제한 상태로 폴더 형태로 로컬 다운로드

# 릴리스 라이프사이클 (Lifecycle) 관리
helm history <릴리스이름>                 # 릴리스 히스토리 확인
helm rollback <릴리스이름> <리비전번호>   # 특정 리비전으로 롤백
```
> **참고:** `rollback` 시 기술적으로 과거 리비전으로 되돌아가는 것이 아니라, 해당 설정값을 바탕으로 **새로운 리비전이 생성**됩니다. (예: 리비전 1로 롤백 -> 리비전 3으로 새로 생성됨)

---

## 4. Kustomize
템플릿 언어를 사용하지 않고, 순수 YAML 파일과 패치(Patch) 개념만으로 환경별 설정을 관리하는 도구입니다.

### 핵심 개념: Base와 Overlay
* **Base:** 공통으로 사용할 기본 리소스 정의 (`../../base` 등)
* **Overlay:** dev, stage, prod 등 환경별로 다르게 덮어쓸 리소스와 패치 정의
    * Overlay 폴더 내에 환경별 고유 리소스 파일 추가 가능
    * Base 리소스를 명시적으로 삭제(patch delete)하지 않는 한 기본적으로 유지됨

### 동작 원리 및 명령어
`kustomization.yaml` 파일에 관리할 리소스 목록과 패치 방법을 정의합니다.

```bash
# kustomization.yaml 파일을 읽어 Base와 Overlay가 모두 적용된 최종 YAML 출력 (클러스터 적용 X)
kustomize build k8s/

# 생성된 최종 YAML을 클러스터에 바로 적용
kustomize build k8s/ | kubectl apply -f -
# 또는 kubectl 내장 kustomize 기능 사용
kubectl apply -k k8s/

# 적용된 리소스 삭제
kubectl delete -k k8s/
```

### Transformer와 Patch
* **Transformer:** 네임스페이스, 라벨, 어노테이션 등 여러 리소스에 공통으로 일괄 적용해야 할 때 사용
* **Patch:** 특정 리소스를 대상으로 세밀한 변경(추가, 수정, 삭제)을 적용할 때 사용

**1. JSON Patch 형식**
```yaml
# 예시: spec.replicas 값을 5로 변경
- target:
    kind: Deployment
    name: my-app
  patch: |-
    - op: replace
      path: /spec/replicas
      value: 5
```
> **리스트(List) 수정:** `path: /spec/containers/0` 처럼 인덱스 지정. 제일 마지막 인덱스는 `0` 대신 `-` 사용.

**2. Strategic Merge Patch 형식**
`apiVersion`, `kind`, `metadata.name`을 기준으로 타겟을 찾아 병합합니다. (별도 파일로 분리하여 참조 가능)
```yaml
# 예시: spec.replicas 값을 3으로 변경
patches:
  - patch: |-
      apiVersion: apps/v1
      kind: Deployment
      metadata:
        name: nginx
      spec:
        replicas: 3
```
> **리스트 삭제:** 삭제를 원하는 키값과 함께 `$patch: delete` 지시어를 작성합니다.

### Components
공통 기능을 모듈처럼 재사용할 수 있게 작성해 둔 단위입니다.
* `resources`가 아닌 `components` 항목에 명시하여 사용합니다.
* Component 내부에서 Base를 참조할 경우 중복 참조 에러가 발생할 수 있으므로, **Component 단독 적용을 피하고 항상 Overlay에서 조립하여 사용**해야 합니다.

---

## 5. Helm vs Kustomize 사용 시기 비교

| 도구 | 사용하기 좋은 상황 |
| :--- | :--- |
| **Helm** | • Redis, MySQL, Prometheus 등 **기성 오픈소스 앱** 설치 시<br>• 설치/업그레이드/롤백을 **단일 명령**으로 관리하고 싶을 때<br>• 팀 내 애플리케이션을 차트로 묶어 **배포 패키지**로 공유할 때 |
| **Kustomize** | • 자사 서비스 YAML을 직접 관리하며 **dev/stage/prod 환경별 미세 조정**이 필요할 때<br>• 복잡한 템플릿 언어 대신 **YAML + 패치** 형태의 직관적인 관리를 원할 때<br>• GitOps (ArgoCD, Flux 등) 기반의 **Base/Overlay 패턴**을 활용할 때 |

---

## 6. 로그 확인 필수 명령어

* **`kubectl logs <Pod이름>`**
    * Pod 안에서 실행 중인 애플리케이션의 컨테이너 로그 확인
* **`crictl logs <컨테이너ID>`**
    * 쿠버네티스 컴포넌트나 API 장애로 `kubectl` 사용이 불가능할 때, 노드에 직접 접속하여 컨테이너 런타임 로그 확인
* **`journalctl`**
    * `kubelet`, `docker`, `containerd` 등 호스트 머신의 시스템 서비스 로그 확인
    * 사용 예: `journalctl -u kubelet -f` (kubelet 서비스 로그 실시간 확인)
