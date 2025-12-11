
# Rollout and Versioning (Deployment)

## 1. Rollout과 Revision

- **Deployment의 Pod 템플릿(spec.template)이 변경**되면, 새로운 **rollout**이 트리거된다.
- 이때 Kubernetes는 각 버전에 대해 **revision 번호**를 부여한다.  
  - 실제로는 `ReplicaSet`에 `deployment.kubernetes.io/revision` 라벨로 관리된다.
  - 동일한 Deployment에 대해 Pod 템플릿이 바뀔 때마다 revision이 증가한다.

### rollout 관련 기본 명령어

```bash
# 현재 rollout 상태 확인
kubectl rollout status deployment/myapp-deployment

# rollout 히스토리 확인
kubectl rollout history deployment/myapp-deployment

# 특정 revision으로 롤백
kubectl rollout undo deployment/myapp-deployment --to-revision=2

# 직전 버전으로 롤백
kubectl rollout undo deployment/myapp-deployment
````

> 일반 형태:
> `kubectl rollout <subcommand> <리소스종류>/<이름>`
> 예: `kubectl rollout status deployment/myapp-deployment`

## 2. Deployment 업데이트 방법

Deployment의 새로운 버전 배포(업데이트)는 보통 두 가지 방식으로 한다.

### 2.1 `kubectl apply` (선호되는 방식)

* Manifest(YAML)에 이미지 버전 등을 수정한 뒤:

```bash
kubectl apply -f deployment.yaml
```

* 장점:

  * **소스(YAML)**와 **실제 클러스터 상태**가 일치한다.
  * GitOps, 형상관리와 궁합이 좋다.

### 2.2 `kubectl set image` (빠른 패치/테스트용)

```bash
kubectl set image deployment/myapp-deployment \
  myapp-container=myimage:v2
```

* 장점:

  * CLI에서 빠르게 이미지 버전만 바꾸고 싶을 때 편리하다.
* 주의점:

  * YAML 파일을 수정하지 않으면,
    **클러스터 상태와 로컬 YAML 내용이 달라질 수 있음**
    → 나중에 `kubectl apply -f deployment.yaml`을 하면 예전 버전으로 되돌아갈 수 있다.

## 3. Deployment Strategy (배포 전략)

Deployment는 크게 두 가지 `strategy.type`을 지원한다.

### 3.1 Recreate

* 설명:

  * 기존 버전의 Pod를 **모두 종료**한 뒤
  * 새 버전 Pod를 **그 후에** 생성하는 방식.
* 특징:

  * 업데이트 시점에 **서비스 다운타임**이 발생할 수 있다.
  * 고가용성이 중요하지 않거나,
    **동시에 두 버전이 떠 있으면 안 되는 경우**(예: DB schema 문제가 있는 경우)에 사용한다.
* 설정 예시:

```yaml
spec:
  strategy:
    type: Recreate
```

### 3.2 RollingUpdate (기본값)

* 설명:

  * 기존 Pod를 **조금씩 줄이면서** 동시에 새 버전 Pod를 **조금씩 늘려가는** 방식.
  * 실제로는 `maxUnavailable`, `maxSurge` 파라미터로 조절한다.
* 특징:

  * **기본(default) 전략**이다.
  * 정상적인 설정이면 **다운타임 없이 점진적 배포**가 가능하다.
* 설정 예시:

```yaml
spec:
  strategy:
    type: RollingUpdate
    rollingUpdate:
      maxUnavailable: 1   # 동시에 빠져도 되는 기존 Pod 수 (또는 비율)
      maxSurge: 1         # 원하는 replicas 수보다 더 많이 띄워도 되는 새 Pod 수 (또는 비율)
```

* “instance 한 개씩 지우고 다시 생성”이라는 표현보다
  → “설정된 비율만큼 기존 Pod를 줄이고, 새 Pod를 늘려가는 방식”이라고 이해하면 된다.

## 4. Rollback (롤백)

Deployment 업데이트 후 문제가 있을 경우, 이전 버전으로 되돌릴 수 있다.

```bash
# 직전 revision으로 롤백
kubectl rollout undo deployment/myapp-deployment

# 특정 revision으로 롤백
kubectl rollout undo deployment/myapp-deployment --to-revision=3
```

* `kubectl rollout history`로 revision 목록을 확인한 뒤, 원하는 revision으로 되돌릴 수 있다.
* 롤백도 결국 새로운 rollout이므로, **새로운 revision 번호**가 부여된다.

