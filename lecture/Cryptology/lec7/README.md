## Stream 암호와 난수 생성

# Random number Uses
- Nonce - 한번 사용하고 버리는 random한 숫자로, 인증 or reply 방지용
- Session key
- Public key generation
- Keystream for one time pad

# 난수
- 통계적으로 random
- uniform하게 분포
- 독립적이여야 함
- 어떤 난수가 다음에 나올지 예상하지 못해야 함

# PRNG
- Pseudo random Number Generator - 가상 난수 생성기
- Deterministic한 알고리즘에 기반하여 난수 생성
- - 알고리즘 기반이다보니, 진정한 의미에서의 난수가 아님
- - 난수의 주기가 존재
- - Randomness test 통과 가능 

# TRNG
- True random Number Generator - 진짜 난수 생성
- Entropy source(input source)를 통해 새로운 난수 생성
- 굉장히 random하며, 현실에서 발생하는 랜덤한 현상을 기반으로 난수 생성
- TRNG는 아날로그 환경 신호를 이진 출력으로 변환하여 사용함으로써 난수 생성
- 시스템 외부의 엔트로피에 의존하기 때문에 예측 불가

## PRNG && TRNG
![alt text](image.png)
- TRNG는 디지털 값으로 변환
- PRNG는 open-ended방식으로, bit stream이 출력으로 나옴
- PRF는 fixed length방식으로, 고정된 값으로 나옴. 또한 User ID, App ID 같은 Context-specific value 사용

# PRNG Requirements
- Randomness
- - Uniformity, scalablity, consistency
- Unpredictability
- - seed 값 예측이 어려워야 함
- - **Forward unpredictability** - Seed를 모르면, sequence 예측 불가
- - **Backward unpredictability** - 이미 생성된 숫자로 seed 예측 불가
- Secure
- - PRNG의 sequence를 정하는 값이기 때문에 안전해야 함. Seed가 같으면 sequence가 같으므로 test 가능
- - Seed 값을 알면, output을 알 수 있음
- - Seed 자체가 random해야 함

# Seed REquirements
- seed는 secure && unpredictable 해야 함
- 보통 Seed는 TRNG에 의해 생성 
![alt text](image-1.png)

## Random number Generator
# Linear Congruential Generator
- x0 = seed로 두고, 다음 x0을 구하는 방식
- 안전하지 않음
- ![alt text](image-2.png)

# Blum Blum Shub Generator
- 공개 키 알고리즘 기반
- ![alt text](image-3.png)
- 반복적인 계산
- xi의 bit중 가장 왼쪽 비트를 출력함으로써 매 계산마다 1bit 출력
- ![alt text](image-4.png)
- Unpredictable 해서, next-bit test를 통과
- N을 인수분해 하는 것이 어려움
- - 인수분해가 어려운 것에 의존하기 때문에 느림
- - Key generation할 때 좋음

# ANSI X6 PRG
- ![alt text](image-5.png)
- 생성되는 random number은 Ri이고, DES를 사용했기 때문에 Ri의 크기는 64bit
- Vi+1은 다음 Vi값으로, 반복적으로 실행됨

# CTR_DRBF
- Counter mod determinisic random bit generator
- ![alt text](image-6.png)
- Generate key의 input 생성 (Key)
- 초기에 v와 key 값은 0일 수 있음.
- 한 block의 크기가 128bit인데, seed의 length보다 작으면 반복해서 생성
Seed length = key length + output(input) block length
처음엔 v가 들어가겠지만, 나중에는 v+1이 들어가고, v+2.. 가 들어 감

- ![alt text](image-7.png)
- Sudo random number이라서, 많이 생성되면 주기가 있어서 반복됨.
- Reset을 시키는데, 이걸 reseed_interval 이라고 함
- 걸리면 새로운 seed를 만듦

# RC4 – Stream cipher
-	가장 일반적인 방법이였지만, 최근 깨짐
-	간단하면서도 stream cipher의 특징을 잘 보여줌

256장의 카드가 검은 봉투에 들어있다고 가정
카드를 꺼내면 그게 random number 
카드를 다시 집어넣음

매번 빼낸 카드를 random 수로 사용
카드와 평문을 XOR -> 암호문
- ![alt text](image-8.png)
- Key가 16개, T는 256개라고 하면, 중복되는 key가 존재

- ![alt text](image-9.png)
- ![alt text](image-10.png)
i부터 0까지 섞고, 한 바이트 씩 암호

# RC4 Security
-	결과가 매우 non-linear해서 잘 사용 했었음
-	절대 같은 key 재사용 X
-	지금은 안전하지 않음
-	RC4는 TLS에서 금지되어 있음
