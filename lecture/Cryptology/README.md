## 용어 정리
- **Cipher**은 평문을 암호문으로 바꾸는 알고리즘
- **Encipher(encrypt)** 암호화
- **Decipher(decrypt)** 복호화
- **Cryptography** 암호생성 분야의 암호학
- **Cryptanalysis(codebreaking)** 암호풀이 분야의 암호학
- **Cryptology** 암호학의 큰 범위(Cryptography+Cryptanalysis)

### Cryptography
- **대칭형 암호**는 암호를 생성할 때와 풀 때의 key가 같은 암호
- **비대칭형 암호**는 암호를 생성할 때의 key와 암호를 풀 때의 key가 다른 암호

## 암호의 특징
- 치환을 통해서 원래 있던 문자를 바꾸는 방식
- 글자의 배열을 바꾸는 방식

- **대칭형 암호**는 하나의 키를 사용하면서 비밀 키 방식
- **비대칭형 암호**는 두개의 키를 사용하면서 하나는 공개 키, 하나는 개인 키로 사용하는 방식

- 암호화의 단위는 block 단위거나 bit 단위로 나눌 수 있음

### Cryptanalysis
- 주 목적은 key를 알아내는 것
## 일반적인 접근
- # **cryptanalytic attack**
- 여러가지 암호 분석 방식이 존재
	암호문만 가지고 있는 경우 
	암호문과 평문을 가지고 있는 경우
	평문을 선택하고, 평문에 대한 암호문을 얻을 수 있는 경우
	암호문을 선택하고, 평문을 얻을 수 있는 경우
이러한 경우들에도 key를 얻기가 어려움

- **brute-force attack**
- key의 bit수가 많아질수록 시간이 엄청나게 걸리기 때문에 어려움

## More Definition
- **Unconditional security**는 절대 깨지지 않는 암호로, 암호의 이상적인 모습이지만 불가능
- **Computational security**는 계산은 가능한데, 현실에서는 시간이 부족해서 해결을 못하도록 하는 방식
- 현재 가장 흔하게 사용하는 128bits key는 **Computational security** 방식이다



