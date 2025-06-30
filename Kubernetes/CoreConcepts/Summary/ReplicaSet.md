# 📑 ReplicaSet & Replication Controller

---

## 🔄 목적

ReplicaSet은 Pod의 복제본을 유지하여 **항상 원하는 수의 Pod가 실행**되도록 보장합니다.  
즉, 한 Pod가 실패해도 다른 복제본이 자동으로 실행되어 **고가용성(High Availability)** 을 유지합니다.

---

## ☝️ 단일 Pod의 유지

- 단 하나의 Pod만 필요하더라도, **ReplicaSet(또는 Replication Controller)** 를 통해 관리하면  
  Pod가 죽었을 때 자동으로 새로운 Pod가 생성되어 항상 1개의 인스턴스가 유지됩니다.

---

## 🌐 클러스터 기반 복제

- Replication Controller는 **로드밸런싱 목적**으로 여러 Pod를 생성 가능
- 특정 노드의 자원이 부족하면, 클러스터 내 **다른 노드에 Pod를 분산 배치**함
- 이는 컨트롤러가 **클러스터 전반의 상태를 알고** 있기 때문에 가능함

---

## 🆚 Replication Controller vs ReplicaSet

| 항목                     | Replication Controller        | ReplicaSet               |
|--------------------------|-------------------------------|---------------------------|
| 방식                     | 구버전                        | 현재 권장되는 방식       |
| API 버전                | v1                            | apps/v1                   |
| Selector 기능            | 제한적                        | label 기반 정교한 선택 가능 |
| 사용 여부                | 더 이상 사용 권장하지 않음    | ✅ 사용 권장됨            |

---

## 🛠 ReplicaSet 정의 방법

1. **Definition File 작성**
   - `apiVersion`: 반드시 `apps/v1` 사용
   - `kind`: `ReplicaSet`
   - `metadata`: 이름 등 메타 정보 작성
   - `spec`:
     - `replicas`: 원하는 복제 Pod 수 설정
     - `selector`: 어떤 Pod를 이 ReplicaSet이 관리할지 지정
       - `matchLabels`: Pod의 `labels`와 일치해야 함
     - `template`: 복제될 Pod의 정의 포함 (`metadata` 및 `spec` 필드 필요)

> ✅ `selector`를 명시해야 하는 이유:  
> ReplicaSet은 **자신이 생성하지 않은 Pod**도 관리할 수 있기 때문에, 어떤 Pod를 추적할지 명확히 해야 함

---

## 🛠 Replication Controller 정의 방식

1. `apiVersion`: `v1`
2. `kind`: `ReplicationController`
3. `spec`:
   - `replicas`
   - `selector`
   - `template`: Pod 정의 포함

> 🔄 Pod 정의는 기존 Pod의 `metadata` 및 `spec`을 복사해서 사용

---

## 📈 스케일링 방법 (Pod 수 조절)

### 1. YAML 파일 수정 후 재적용
```bash
# replicas 수를 수정한 후
kubectl replace -f replicaset-definition.yml
kubectl scale --replicas=6 -f replicaset-definition.yml
# 또는
kubectl scale --replicas=6 replicaset myapp-replicaset