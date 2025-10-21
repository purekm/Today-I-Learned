
---

# 가상 메모리 & 페이지 교체 총정리

> **가상 메모리(Virtual Memory)** = 실제 RAM보다 큰 **논리적 주소 공간**을 각 프로세스에 독립적으로 제공하는 메모리 관리 기법.

---

## ✅ 가상 메모리의 목적과 장점

* **독립적 주소 공간**: 프로세스마다 0번 주소부터 끝까지 논리적으로 사용 가능(보호/격리).
* **일부만 로딩(요구 페이징)**: 전체 프로그램이 아닌 **필요한 페이지만** 메모리에 적재.
* **메모리 한계 완화**: 논리 메모리를 물리 메모리보다 **더 많이 할당 가능**.
* **성능**: 불필요한 I/O 감소 → 평균 접근 지연 **감소**.
* **공유 용이**: 공유 라이브러리/공유 메모리로 **코드·데이터 공유**.
* **프로세스 생성 효율**: 포크 후 **COW(Copy-on-Write)** 등으로 빠른 생성.
* **동시성 향상**: 여러 프로세스 동시 실행, I/O 중첩으로 **CPU 활용도↑**.

> 참고 이미지
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/f5088fdf-0830-4996-aca3-659cb46a4cf0)
> hole(빈 구간)에 **공유 라이브러리/공유 메모리**가 들어감
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1b19da50-5c11-4c1e-98b5-bb20be8cef45)

---

## 🧩 요구 페이징(Demand Paging)

* **필요한 페이지만** 디스크(백킹스토어)에서 **그때그때** 메모리로 로드.
* 초기 구동 시 페이지가 비어 있어 **page fault가 잦을 수 있음** → **pre-paging**(선적재)로 완화.
* 하드웨어 전제:

  1. **유효/무효 비트**가 있는 페이지 테이블
  2. **2차 저장장치(swap)**
  3. **명령 재시작(Instruction Restart)**

> 참고 이미지
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c9cb3485-0898-4b04-8c1e-993179a888d1)
> **Invalid**(무효)이면 페이지 폴트
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/5beb0f30-3c41-4e0c-bc16-c4c32de8205d)

---

## 🔁 주소 변환과 TLB

1. **CPU**: 가상주소(VA) 생성
2. **MMU**: TLB 조회

   * **Hit** → 물리주소(PA) 즉시 생성
   * **Miss** → 페이지 테이블 워크(PTE 확인)
3. **PTE 유효** → TLB 적재 후 접근
4. **PTE 무효** → **페이지 폴트** 처리 진입

> 참고 이미지
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/71af5be2-d6d9-452e-b08e-aafee0205233)

---

## ⚙️ 페이지 폴트 처리 절차

**Steps in Handling Page Fault**

1. **페이지 참조** → PTE 무효면 **트랩** 발생(OS로 진입)
2. **OS 판단**: 접근이 **합법(VMA 내)** 인지 검사
3. **Free frame** 탐색(없으면 교체)
4. **백킹스토어에서 페이지 로드**(또는 zero-fill/COW)
5. **PTE 업데이트**(PFN, 권한, Present=1) + **TLB 갱신**
6. **명령 재시작**(Instruction Restart)

> 참고 이미지
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c3bec95d-2542-4ddd-89b0-6a4aa163e59f)

**메이저/마이너 구분**

* **Major**: 페이지가 **RAM에 없음** → **디스크 I/O** 필요 → 느림
* **Minor**: 페이지는 RAM에 **이미 존재**, 단지 **이 프로세스의 매핑만 없음**(공유 라이브러리, COW 등) → **PTE만 갱신** → 빠름

---

## 🧠 Instruction Restart 주의

* 일부 연산은 중간에 폴트 발생 시 **원자성/정합성** 문제가 생길 수 있음.
  → **사전 선적재** 또는 **임시 레지스터 보관/복구** 전략 필요.

> 참고 이미지
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/c28bde13-d772-4d6e-8b97-7a5df8cb26df)

---

## 📦 Free Frame List & Modified / Compressed

* **Free Frame List**: 즉시 재사용 가능한 **빈 물리 프레임** 모음(필요 시 **zero-fill-on-demand** 후 제공).
* **Modified(Dirty) List**: **수정된 페이지**(디스크와 내용 다름)를 일단 모아둠 → **flush daemon**이 **비동기 write-back** 후 Free로 이동.
  *(I/O 묶음 처리로 효율↑)*
* **Compressed List**: **RAM 부족 시**, 스왑 전에 **RAM 안에서 페이지 압축 저장**(여러 페이지를 1프레임에).
  → **스왑 I/O를 지연/감소**(공간 효율↑, CPU 소모는 있음).
  *(macOS compressed memory, Linux zram/zswap 등)*

> **중요 구분**
>
> * **Modified List** = *Dirty 페이지의 쓰기 대기열* (언젠가 디스크로 감)
> * **Compressed List** = *스왑 회피를 위한 RAM 내 압축 저장* (디스크로 안 감)

---

## ⏱️ 성능 모델(EAT)

* **EAT = (1 - p) × 메모리 접근시간 + p × (Fault 서비스 시간)**
* 예) 메모리 200ns, Page Fault 8ms(=8,000,000ns):
  `EAT = 200 + p × 7,999,800(ns)` → **p**에 민감

---

## 🧰 최적화 포인트

* **Swap 공간**: 파일시스템 I/O보다 **swap 공간** 접근이 일반적으로 빠름.
* **익명 메모리**: 실행 중 생성되는 **anonymous memory**는 swap 사용.
* **COW**: fork 후 페이지 복사 대신 **공유 + 최초 쓰기 시 복사**로 최적화.

  > ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/8752976b-b1e2-4785-a896-eb8a0e3b4cba)
  > ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ceb26f4e-6d4a-4c76-b119-7a5cceee0f89)

---

## 🔄 페이지 교체(Replacement)

* **왜 필요?** 프레임이 가득 찼는데 새 페이지를 올려야 할 때 **희생 페이지(victim)** 선택.
* 흐름: victim 선정 → **Dirty면 write-back** → PTE/TLB 갱신 → 재시작
* **Local vs Global 교체**: 자기 프레임에서만/전체에서 교체(장단점 존재)
* **Dirty bit** 고려: 가능한 **clean 페이지 우선** 희생 → I/O 절감

---

## 📈 레퍼런스 스트링 & 알고리즘 평가

* **Reference String**: 페이지 접근 순서열 → 알고리즘 성능 분석에 사용
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/218a5d23-4396-4c1d-89c6-f20debcbc8d3)

### 대표 알고리즘

1. **FIFO**: 먼저 들어온 페이지부터 교체(단순, **Belady’s anomaly** 발생 가능)
   ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7c6b5223-f750-4c1e-8d68-fb70474ee00d)

2. **Optimal(MIN)**: **미래에 가장 늦게** 사용될 페이지 교체(이론적 최적, 구현 불가)
   ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/7a86c852-e356-4902-b9aa-436b6fa5f244)

3. **LRU**: **가장 오래전에 사용된** 페이지 교체(현실적·성능 우수, 구현 비용↑)
   ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/67d4362d-9962-4113-b6af-77e939e33e40)

4. **LRU 근사(Reference-bit 계열)**

   * **Second Chance(Clock)**: R=1이면 기회 부여 후 0으로 리셋, R=0이면 교체
     ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/05fbbb3a-0055-4e3c-9a95-69c25a294390)
   * **Enhanced Second Chance**: (R, Dirty)까지 고려 → (0,0) 우선
     ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/cb5f68aa-d3ef-4ef4-8c24-e7650a0651e4)
   * **Additional Reference Bits**: 주기적으로 비트 쉬프트로 과거 사용 흔적 기록
     ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/e6194507-cf39-4004-a733-fcc46459aa5c)

> **LRU/OPT는 Stack Algorithm** → **Belady’s anomaly 없음**
> ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b56d945d-58cf-4c7e-a19b-1e0f64022a0d)

**Counting 계열(LFU/MFU)**: 빈도 기반(구현 비용↑, OPT 근접성↓)
**Page-Buffering**: 소규모 풀로 즉시 대체/복구, I/O 중첩(병행) 가능

---

## 🧮 프레임 할당

* **Equal/Proportional/Priority 할당**
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/bc151598-7aa0-4859-bf50-8b327d25ae1a)
* **Global vs Local**: 전체/자기 것 중 교체 선택

**Reclaiming**: Free frame 임계치 도달 시 **선제 교체**
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/3b14a8a6-540a-4668-8935-582de97dc83c)

---

## 🧭 NUMA

* 노드 간 메모리 접근 지연이 **비균일(Non-Uniform)**
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/e42c8863-5638-4438-b3ba-a2a4928ebd9e)

---

## 🔥 스래싱(Thrashing)

* **Page Fault 폭증** → 페이징에 시간 대부분 소비 → **CPU 활용도 급락**
* OS가 “I/O가 한가하네? 더 태워!” 오판 시 악화

### 대책

* **Locality 모델**: 시간/공간 지역성 활용
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/f07c275d-8d57-4bee-ad65-52c3a4e8acb4)
* **Working Set 모델**: 최근 윈도우 내 참조 페이지 집합(W) 유지, `D > m`이면 스래싱
* **Page-Fault Frequency(PFF)**: 폴트율 기반으로 동적 프레임 증감(로컬 정책)

---

## 🧱 커널 메모리 할당자

* **Buddy System**: 큰 블록을 2의 거듭제곱으로 쪼개 사용 후 병합
* **Slab Allocator**: 커널 오브젝트 크기에 맞춘 **슬랩 캐시**로 빠르고 파편화↓
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6f3f50aa-d3d4-486c-8c25-cd11bf288962)

---

## 🧯 기타 주제

* **Pre-paging**: 데이터 파일 등 **예측 가능한 접근**엔 선적재가 유효.
* **페이지 크기**: 작을수록 **내부 단편화↓**, 하지만 **TLB 효율**과 트레이드오프
  ![image](https://github.com/purekm/Today-I-Learned/assets/90774046/48382a01-10d8-4e8d-a75d-026c6914a51a)
* **TLB Reach = (TLB 엔트리 수 × 페이지 크기)**: 클수록 좋음.
* **I/O interlock**: I/O 버퍼가 있는 페이지는 교체 금지(핀ning).
* **OS별 프리페치**:

  * Linux: LRU 계열 리스트(활성/비활성)로 **앞쪽이 자주 사용**
  * Windows: **Clustering**(폴트 근처 앞뒤로 묶어 다수 선적재)

---

### 📌 기억하기 좋은 한 장 요약

* **VM = 보호·효율·확장성**
* **TLB → PT → Page Fault**
* **Minor(Mem에 있음) vs Major(Disk I/O)**
* **Modified = Dirty write-back 대기, Compressed = RAM 압축 저장**
* **LRU~Clock(Second Chance)**, **Belady’s anomaly(FIFO)**
* **Working Set / PFF로 스래싱 제어**

---

