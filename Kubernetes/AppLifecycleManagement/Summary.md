# Environment 설정 방식

## 1. Plain Key-Value

```yaml
env:
  - name: APP_COLOR
    value: pink
```

## 2. ConfigMap

### 모든 키 가져오기

```yaml
envFrom:
  - configMapRef:
      name: my-config
```

### 특정 키 가져오기

```yaml
env:
  - name: APP_COLOR
    valueFrom:
      configMapKeyRef:
        name: my-config
        key: color
```

## 3. Secret

### 특정 키 가져오기

```yaml
env:
  - name: APP_COLOR
    valueFrom:
      secretKeyRef:
        name: my-secret
        key: color
```

### Secret 생성 방식

* definition 파일에서 `data` 사용 시 base64 인코딩 필요
* 인코딩 없이 사용하려면 `stringData` 사용
* imperative 방식: `kubectl create secret generic my-secret --from-literal=password=mypwd`

### Secret 디코딩

```bash
echo "<base64>" | base64 --decode
```

### Secret 보안 특성

* base64 인코딩일 뿐 안전하지 않음
* etcd에서는 Encryption at Rest 활성화 필요

---

# ConfigMap vs Secret

| 항목     | ConfigMap  | Secret            |
| ------ | ---------- | ----------------- |
| 용도     | 민감하지 않은 설정 | 민감한 데이터           |
| 저장 방식  | 평문         | base64 인코딩        |
| 자동 인코딩 | 없음         | 가능 (`stringData`) |
| 보안 수준  | 낮음         | 상대적으로 높지만 완전하지 않음 |

---

# Multi-Container Design Patterns

## 1. Co-located Containers

* 여러 컨테이너가 하나의 Pod에서 함께 실행
* 자원(Volume 등) 공유

## 2. Init Containers

* 메인 컨테이너 **시작 전** 한 번만 실행
* `containers:`와 별도로 `initContainers:` 섹션 필요

```yaml
initContainers:
  - name: init
    image: busybox
    command: ["sh", "-c", "echo init"]
```

## 3. Sidecar Containers

* 메인 컨테이너와 **함께 계속 실행됨**
* 로그 수집, 프록시, 동기화 작업 등에 사용
* 형태는 일반 컨테이너와 동일

---

# Volume

* Pod 안에서 사용하는 저장소
* 여러 컨테이너가 공유 가능

## Volume 종류

* **emptyDir**: Pod가 삭제되면 데이터도 삭제
* **hostPath**: 노드에 저장, 노드가 유지되면 데이터 유지
* **configMap/secret**: 설정값 전달 목적
* **PVC**: Pod 삭제해도 데이터 유지 (Persistent Volume 사용)

## VolumeMount

* 볼륨을 특정 컨테이너 내부 경로에 연결

---

# Init Container 확인

```bash
kubectl get pods
```

* 컨테이너 개수만으로 판단 불가
* init 컨테이너는 실행 후 종료될 수 있음

자세히 확인:

```bash
kubectl describe pod <pod-name>
```

---

# AutoScaling

## Horizontal Pod Autoscaler (HPA)

* Pod **개수** 자동 조절

## Vertical Pod Autoscaler (VPA)

* Pod에 **할당된 자원(CPU/Memory)** 자동 조절

---

# Logs 확인 방법

## 1. 앱 로그

```bash
kubectl logs <pod>
```

## 2. 리소스 상태 확인

```bash
kubectl describe <resource> <name>
```

## 3. 클러스터 이벤트 확인

```bash
kubectl events
```
