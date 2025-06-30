````markdown
# 📘 Kubernetes Pod 명령어 & 실습 예시 정리

---

## 📌 1. 모든 Pod 목록 확인

```bash
kubectl get pods
````

![alt text](image.png)

---

## 📥 2. 이미지로 Pod 생성

```bash
kubectl run <pod-name> --image=<image-name>
```

예시:

```bash
kubectl run nginx --image=nginx
```

![alt text](image-1.png)

---

## 🔎 3. 특정 이름/라벨/노드에 있는 Pod 찾기

* Label: `busybox`
* Node: `controlplane`

```bash
kubectl get pods -o wide
kubectl get pods --selector run=busybox -o wide
```

![alt text](image-3.png)
![alt text](image-2.png)

---

## 📦 4. 컨테이너 수 및 사용된 이미지 확인

* Container 수: 2개
* 사용된 이미지: `nginx`, `agentx`

```bash
kubectl get pods <pod-name> -o jsonpath="{.spec.containers[*].image}"
kubectl describe pod <pod-name>
```

![alt text](image-5.png)
![alt text](image-4.png)

---

## ❌ 5. Pod 삭제

```bash
kubectl delete pod <pod-name>
```

![alt text](image-6.png)

---

## ➕ 6. redis123 이미지를 사용한 redis Pod 생성

```bash
kubectl run redis --image=redis123
```

![alt text](image-7.png)

---

## 🛠 7. Pod 수정

```bash
kubectl edit pod <pod-name>
```

![alt text](image-8.png)

```
```
