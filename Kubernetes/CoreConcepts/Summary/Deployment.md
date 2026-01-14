
---

# Kubernetes Deployment와 Rolling Update

## Deployment란?

Deployment는 **Pod를 관리하는 오브젝트**로,
애플리케이션의 **배포(Deployment)**, **업데이트(Update)**, **롤백(Rollback)** 등을 자동화한다.

과거에는 ReplicaSet(또는 ReplicationController)을 직접 생성해
여러 Pod를 유지했지만, Deployment를 사용하면 ReplicaSet을 자동으로 생성하고 관리할 수 있다.


---

## Deployment의 주요 역할

1. **Pod 개수 유지**

   * 정의된 `replicas` 수를 항상 보장한다.
   * Pod가 비정상 종료되면 자동으로 새로운 Pod를 생성한다.

2. **Rolling Update**

   * 여러 Pod(인스턴스)를 한 번에 모두 교체하지 않고,
     **하나씩 점진적으로 업데이트**하여 서비스 중단을 방지한다.

3. **Rollback**

   * 업데이트 중 오류 발생 시 이전 버전으로 **자동 복구(rollback)** 가능하다.

4. **ReplicaSet 자동 관리**

   * 새로운 버전의 Deployment를 적용하면 새로운 ReplicaSet이 생성되고,
     이전 ReplicaSet은 자동으로 축소(scale down)된다.

---

## Rolling Update란?

Rolling Update는 **무중단 배포(Zero Downtime Deployment)**를 위한 기본 전략이다.
Pod를 한 번에 모두 교체하지 않고, 다음과 같은 순서로 점진적으로 교체한다.

1. 기존 Pod 중 일부를 종료 (`maxUnavailable` 만큼)
2. 새 버전 Pod를 생성 (`maxSurge` 만큼)
3. 모든 Pod가 새 버전으로 교체될 때까지 반복

이 과정을 통해 서비스는 항상 일정 수의 Pod가 유지되므로
트래픽 손실 없이 안정적으로 업데이트가 가능하다.

---

## Deployment 동작 과정

1. `kubectl apply -f deployment.yaml` 명령 실행
   → Deployment가 생성됨
2. Deployment는 내부적으로 ReplicaSet을 자동 생성
3. ReplicaSet이 Pod들을 생성
4. 업데이트 시 새 ReplicaSet이 생성되고, 기존 ReplicaSet은 점진적으로 축소됨
5. 모든 Pod가 새 버전으로 교체되면 구 버전 ReplicaSet은 유지되지만 scale 0 상태로 남음
   (→ 필요 시 `rollback` 가능)


---

## 정리

| 항목      | 설명                                        |
| ------- | ----------------------------------------- |
| 관리 단위   | Deployment                                |
| 내부 구성   | ReplicaSet, Pod                           |
| 업데이트 방식 | Rolling Update (무중단 배포)                   |
| 복구 기능   | Rollback 지원                               |
| 주요 명령   | `apply`, `rollout status`, `rollout undo` |
| 장점      | 자동화된 배포/복구, 무중단 서비스 유지                    |

---
