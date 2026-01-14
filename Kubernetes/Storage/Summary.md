
---

# Kubernetes Storage 정리

## 1. Storage Driver 개념

**Storage Driver**는 여러 개의 **이미지 레이어(image layer)** 를 겹쳐서 **하나의 파일시스템처럼 보이게 하는 기술**입니다.
각 레이어는 불변(읽기 전용, Read-Only)이며, 컨테이너 실행 시 **읽기/쓰기(Read-Write)** 가능한 **Container Layer**가 추가됩니다.
컨테이너 내부 파일 시스템 관리 하는 역할

### Layered Architecture 예시

1. Ubuntu 기본 파일 시스템
2. apt 패키지 설치
3. pip 패키지 설치
4. 소스 코드 복사
5. Entrypoint 업데이트

이러한 구조 덕분에 다음과 같은 장점이 있습니다.

* **저장공간 절약:** 동일한 이미지 레이어를 여러 컨테이너가 공유
* **효율적인 재사용:** 공통 레이어를 재활용 가능
* **변경 분리:** 컨테이너별로 독립된 Read/Write Layer 유지

---

## 2. 데이터 유지 — Volume

Container Layer는 **휘발성**입니다.
컨테이너가 삭제되면 데이터도 함께 사라지므로, 데이터를 유지하려면 **Volume**을 사용해야 합니다.

### Volume 사용 흐름

1. Volume 생성
2. 생성한 Volume을 컨테이너의 재작성 레이어에 마운트
   → 데이터가 Volume에 저장됨

> 볼륨을 직접 생성하지 않고 마운트하려 하면, Docker가 자동으로 볼륨을 생성합니다.

이 과정을 **Volume Mounting**이라고 합니다.

---

## 3. Bind Mount

기본적으로 Docker는 `/var/lib/docker/volumes` 아래에 볼륨 데이터를 저장합니다.
만약 **호스트 시스템의 특정 디렉터리**를 직접 마운트하고 싶다면 **바인드 마운트(Bind Mount)** 를 사용합니다.

* 사용법: 마운트할 **호스트 경로의 전체 경로를 지정**
* 예시: `/home/data:/app/data`

> 차이점:
>
> * **Volume Mount:** Docker가 관리하는 볼륨 디렉터리 사용
> * **Bind Mount:** 호스트의 지정된 경로 사용

---

## 4. Kubernetes의 Volume 종류

| 종류                              | 설명                                      |
| ------------------------------- | --------------------------------------- |
| **emptyDir**                    | Pod가 삭제되면 함께 삭제되는 임시 디렉터리 제공            |
| **configMap**                   | 설정 파일 등 구성 데이터를 파일 형태로 마운트                      |
| **persistentVolumeClaim (PVC)** | 요청된 조건에 맞는 Persistent Volume(PV)을 찾아 연결 |
| **hostPath**                    | 노드의 실제 디렉터리를 그대로 Pod에 마운트 (공유 폴더 느낌)    |

---

## 5. Storage Driver vs Volume Driver

* **Storage Driver:** Docker가 이미지 레이어와 컨테이너 파일시스템을 관리하는 핵심 엔진(컨테이너 안의 파일 저장)
* **Volume Driver:** 외부 스토리지(예: NFS, AWS EBS, Ceph 등)와의 연동을 담당
---

## 6. Container Storage Interface (CSI)

초창기 Kubernetes는 특정 컨테이너 런타임이나 스토리지 시스템에 종속되어 있었습니다.
이를 해결하기 위해 표준 인터페이스를 정의했으며, 대표적으로 다음이 있습니다.

* **CRI (Container Runtime Interface)**
* **CNI (Container Network Interface)**
* **CSI (Container Storage Interface)**

### CSI란?

Kubernetes와 스토리지 드라이버 간의 통신 규칙을 정의한 **표준 인터페이스**입니다.

### CSI 주요 동작

1. **CreateVolume**

   * PVC가 생성되면 Storage Driver에 RPC 호출하여 볼륨 생성 요청
   * RPC를 사용하는 이유: 스토리지 벤더마다 API가 다르기 때문
2. **DeleteVolume**
3. **ControllerPublishVolume**

   * 특정 노드에 볼륨을 연결하는 과정

> Kubernetes는 CSI 표준에 따라 RPC 요청을 보내고,
> 각 스토리지 벤더는 이를 처리하는 **CSI Driver**를 직접 구현하여 API를 호출합니다.

---

## 7. Persistent Volume (PV) & Persistent Volume Claim (PVC)

### 개념

* **PV (Persistent Volume):** 클러스터에 미리 준비된 실제 스토리지 리소스
* **PVC (Persistent Volume Claim):** Pod가 요청하는 스토리지 요구사항

PVC의 조건에 맞는 PV를 찾아 매칭합니다.

### PV 정의 시 주요 항목

* `spec.capacity`
* `spec.accessModes`
* `spec.hostPath` (노드 디스크 사용 시)
* 외부 스토리지의 경우, 다른 스토리지 플러그인 사용

### PVC 매칭 조건

* 충분한 용량 (`Sufficient Capacity`)
* 접근 모드 (`Access Modes`)
* 볼륨 모드 (`Volume Modes`)
* 스토리지 클래스 (`StorageClass`)

> PV와 PVC는 **1:1 관계**입니다.
> PVC 요청보다 큰 PV가 매칭되면, 남는 공간도 그대로 사용됩니다.

여러 PV가 조건에 부합하면 **Selector**를 사용해 특정 PV를 선택할 수 있습니다.

---

## 8. PV Reclaim Policy

PVC가 삭제될 때 PV의 처리 방식은 **`persistentVolumeReclaimPolicy`** 로 결정됩니다.

* **Retain:** PV 및 데이터 유지
* **Delete:** PV 삭제

PVC를 삭제했는데 정책이 Retain이라면, PV는 **Terminating 상태**로 남아있게 됩니다.

---

## 9. StorageClass & 동적 프로비저닝

**StorageClass**는 특정 CSI 드라이버와 설정(템플릿)을 정의한 리소스입니다.
PVC가 생성되면 Kubernetes는 StorageClass의 설정에 따라 CSI 드라이버에 **자동으로 Volume 생성 요청**을 보냅니다.

이 과정을 **Dynamic Provisioning (동적 프로비저닝)** 이라고 합니다.

---

**요약**

* **Storage Driver:** 이미지 레이어 관리
* **Volume / Bind Mount:** 데이터 유지 및 외부 스토리지 연동
* **CSI:** 스토리지 벤더 표준화 인터페이스
* **PV/PVC:** 영구 스토리지 추상화
* **StorageClass:** 동적 프로비저닝의 기반 템플릿

---

Lab
Provisioner 타입에 noprovisioner가 되어있으면 대부분 동적프로비저닝을 지원하지 않음

