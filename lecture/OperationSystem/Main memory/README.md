
---

# 메모리 관리 정리

## CPU 접근 가능한 저장 공간

* **Register**: CPU가 직접 접근 가능, **1 CPU clock**에서 접근 가능 → 빠름
* **Main Memory**: 접근 속도가 느려서 **memory stall** 발생 가능
* **Cache**: CPU와 Main Memory 사이에서 효율을 높이는 역할
* 메모리는 공유 자원이므로 **프로세스 간 침범 방지 필요**

---

## 메모리 보호: Base Register & Limit Register

* **Base Register**: 프로세스 논리 주소 공간의 시작 주소
* **Limit Register**: 프로세스 논리 주소 공간의 크기
* 조건:

  ```
  base ≤ address < base + limit
  ```
* 설정은 **운영체제만 가능**, 사용자 프로그램은 변경 불가

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/2d1dba31-94e7-4250-bbff-91df482b19f4)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1c007f02-d79d-4d89-a264-0017e9414868)

---

## Address Binding

프로그램이 실행되려면 주소가 필요한데, 주소는 언제 결정될까?

1. **Compile time**

   * 메모리 위치가 알려진 경우 절대 주소 생성
   * 하지만 로딩 위치 변경 시 **recompile 필요**

2. **Load time**

   * 상대 주소 사용
   * 로딩 시 실제 물리 주소로 계산

3. **Execution time**

   * 실행 중에도 다른 메모리 위치로 이동 가능
   * Hardware 지원 필요 (swapping, paging)

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/9a31d00f-fe8a-487f-bc22-233163cab2b7)

* 실행할 때 라이브러리 link → **Dynamic Linking**
* **Logical Address**: CPU가 생성
* **Physical Address**: 메모리 유닛이 보는 주소

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1aefc4e4-5c91-4c60-800f-d9a6a8b37dd1)

---

## Dynamic Loading & Linking

* **Dynamic Loading**

  * 필요할 때 routine을 로드
  * unused routine 미로드 → 메모리 효율 ↑
* **Static Linking**

  * 라이브러리 → 실행 파일에 직접 포함
  * 크기 ↑, 독립 실행 가능
* **Dynamic Linking**

  * 실행 시 라이브러리 연결
  * **stub** 존재, OS가 라이브러리 로드 및 공유

---

## Contiguous Allocation

* 연속적인 메모리 할당으로, 메인 메모리 안에 프로세스 주소공간을 할당하는 것 
* **OS**는 low memory에 할당되고 , **user process**는 high memory 할당됨
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/ad1c4ba9-5d17-4ff6-bd69-531237717f8b)

---

## Variable Partition

* 가변 크기의 partition 활용
* 프로세스 종료 시 hole 발생, 인접 partition 병합

---

## Dynamic Storage Allocation

* **First-fit**: 가장 먼저 맞는 hole → 빠름
* **Best-fit**: 가장 작은 hole
* **Worst-fit**: 가장 큰 hole

---

## Fragmentation
연속적 할당으로 인해 발생
* **External**: 전체 공간 충분하지만 연속 X → 할당 불가
* **Internal**: 요청 크기보다 큰 공간 할당 시 남는 메모리 낭비

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/cb4cf360-5da9-4c4a-badb-e92a35d5ac3c)

---

## Paging

* 메모리를 **고정 크기** page/frame으로 분할
* Page Table로 논리 → 물리 주소 변환

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/43e8ef12-3ee6-4e8f-afe0-8a0fd86754d3)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/752aa39b-b810-4c56-a2bc-bb27b9d5bad9)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/b9e2f3ae-a428-41f1-9545-618293cf45e4)

---

## Paging 계산 예시

* page size = 2048 bytes
* process size = 72766 bytes
* → 35 pages + 1086 bytes
* 남는 공간 = **Internal Fragmentation**

---

## Page Table 구현

* **PTBR**: Page Table Base Register
* **PTLR**: Page Table Length Register
* 2번 메모리 접근 필요 → **TLB로 개선**

---

## Translation Look-aside Buffer (TLB)

* 빠른 저장 공간, 병렬 검색
* Context Switch 시 Address-space identifiers 필요

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/2d3b0511-6c95-4f9c-9beb-434c3d5d0822)

1. 페이지를 찾아볼 때 CPU가 해당 페이지의 논리주소를 찾아보고, TLB를 찾아봄. 
2. 만약 TLB에서 hit 되면 물리 메모리 참조에 있는 페이지 찾아봄. miss나면 page table 찾아보고 있으면 해당 페이지를 TLB에 적재하고 물리 메모리 참조, 여기서도 miss가 나면 페이지 폴트 커널 진입
3. 스왑영역에서 페이지 찾아와서 페이지 테이블에 추가 및 TLB에 추가 후 물리 메모리 참조



---

## Effective Access Time

* TLB hit ratio가 높을수록 성능 ↑

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/a9335dc7-fefb-47da-ad7e-2d3a64e22212)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6db90e30-5395-4b8d-9e1c-cd080d9df7d4)

---

## Memory Protection

* Page Table Entry 추가 정보

  * Protection bit
  * Valid/Invalid bit

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/52ed55aa-d69b-47f9-8f25-909bf95f69e2)

---

## Shared Pages

* **Shared Code**: 읽기 전용 코드 공유
* **Private Code**: 독립적 사용

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/20a14dbc-c9d3-432f-9ff1-f702ae06c8e1)

---

## Hierarchical Paging

* page table이 너무 커서 계층 구조로 분할

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/4d02e9bf-7d81-465d-a4d7-bb614eea292d)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/6d73c4d2-0ae2-4c88-a217-6bbb0273542d)

---

## Hashed / Inverted Page Table

* **Hashed Page Table**: 32bit 이상에서 사용
* **Inverted Page Table**: 시스템 전체에 하나만 존재

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/180c23c9-607d-43c3-8a1d-d52a3c4c7cf3)

---

## Swapping

* 메모리 부족 시 프로세스 전체를 디스크로 내보냄

![image](https://github.com/purekm/Today-I-Learned/assets/90774046/fd8abbea-dca1-4a09-bf4d-4bf9a269dbd6)

---

## Swapping on Mobile

* iOS: 메모리 반환 요청, 불응 시 종료
* Android: 메모리 부족 시 앱 종료 후 상태 저장

---
# 프로세스 주소 공간
- Code : 함수 및 명령어 같은 코드 영역
- Data : 초기값이 있는 정적 변수 및 static 변수
- BSS : 초기값이 없는 정적 변수 및 static 변수
- Heap : 동적 변수 (malloc)
- Stack : 지역 변수 및 리턴 어드레스

Data와 BSS의 차이가 뭔가?

=> 초기값이 있으면 실행파일을 그대로 읽어와야 해서 I/O가 발생해 느리지만, 초기값이 없으면 메모리에 0으로만 채우면 되서 빠름. (메모리 최적화 및 효율적)

Heap의 malloc방식

=> malloc할 때 free list에 빈 공간이 있으면 이를 할당해주지만, 빈 공간이 없으면 추가적으로 공간을 할당함.
- 작은 공간을 할당해야 할 때는 시스템콜 brk()로 힙 영역을 늘림으로써 공간을 할당
- 더 큰 공간을 할당해야하면 시스템콜 mmap()으로 heap 공간 외부에 추가적인 공간을 할당
