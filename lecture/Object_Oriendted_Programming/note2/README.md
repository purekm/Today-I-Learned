## Object
- Object는 비슷하지만, 서로 다른 개체
- Class는 비슷한 Objects의 그룹
- Inheritance는 상속으로, 관계를 정의할 수 있음
- 모든 객체는 의도가 있음 -> inheritance도 그에 맞는 의도로 사용해라
- ![alt text](image.png)

# Object란 무엇인가?
- 주변에 있는 것 중에서 사물이든 개념이 되었든, 확실한 경계가 있고, 고유한 의미가 있어야 함(같은 펜 두개가 있어도 객체가 두개 있는 것)
- 경계가 애매한 것은 Identity가 있으면 object로 정의할 수 있음
- Identity를 정의할 때는 구분할 필요가 있는지 없는지에 대한 것이 중요
- 구분할 필요가 없는 것은 attribute (같은 5만원권이 있으면 상관없잖아)

![alt text](image-1.png)

![alt text](image-2.png)
- 추상적인 개념들 : attributes
- Object는 확실한 경계가 있어야 함

![alt text](image-4.png)
- Object는 고유한 주특기가 있어야 함
- 주특기는 다른 객체들과 상호작용 할 수 있는 수단
- 상호작용 하려면 interface or type 을 통해서 가능

# State
- Object는 **state**를 가질 수 있음.
![alt text](image-5.png)

- 언제, 어떻게 요청했느냐에 따라  state를 가질 수 있음.
- Object의 state는 현재 attributes의 value에 의해 결정(커피 머신에 코인을 넣엇을 때의 state, 커피가 없을 때의 state)

***State는 private하게 사용하는 것이 good enginnering practice***

# Identities
- Object는 unique한 identity를 가짐
- Objects = Behavior + state + identity

![alt text](image-6.png)
- button 1개(Java는 new를 해야 새로운 객체가 생김)
- 일란성 쌍둥이는 서로 다른 identity를 가짐

# Messages passing
- Objects는 request(message)를 주고 받음으로써 action을 수행함
- ![alt text](image-7.png)

- Message passing은 다른 Object를 호출하는 것과 같음. (Java: method, C++: member function)
- ![alt text](image-8.png)

- Receiver의 타입에 따라서 같은 message에 대해서 다른 action이 발생할 수 있음(Polymopolism).

- ![alt text](image-9.png)

- 사람이 객체를 위해 일하지말고, 객체가 사람 대신에 일해라(사람이 갑)
- ![alt text](image-10.png)

- Object가 어떻게 action 취하는지는 몰라도 되지만, 어떤 message를 보내야 하는지 알아야 함


***implementation details를 encapsulate하는 것이 good enginnering practice***

# Encapsulation
- interface와 implementation을 구분
- code 재사용과 신뢰성 챙김
- public한 부분은 볼 수 있게 interface에, private한 부분은 implementation에 작성 
- ![alt text](image-11.png)

# Class
- A Class is a group of objects with similar attributes
- Class는 객체의 속성이나 action의 저장소
- ![alt text](image-12.png)

# Object
- Object는 class의 actual instance
- ![alt text](image-13.png)
- Class는 factory, Object는 instance(product)
- **The terms instance and object are interchangeable.**

- Object는 여러 개의 type을 가질 수 있고, 다른 클래스의 object와 같은 type을 가질 수 있음
- ![alt text](image-14.png)
- ClassD가 가질 수 있는 type
- - Class D, Class B, Storable, Runnable
- Class D와 X가 공유하는 type
- - Runnable
- - Class D는 부모의 타입을 다 가질 수 있음

- ![alt text](image-15.png)
- 같은 Class로 만들어진 instance들은 identical attribute를 가지지 못할 수 있지만, 그들은 unique 함 
- Attributes들이 같아도, 다른 객체임

## (Public)Inheritance
- 부모 관계라는 단어로 나타내고 싶은 진짜 의미가 뭘까?
- ![alt text](image-17.png)
- 부모는 general 한 개념을 포함하고, 자식은 부모의 개념 + specialize한 개념
- Mammal은 subclass, Animal은 superclass

- ![alt text](image-18.png)
- 하나의 class는 superclass 이면서, subclass가 될 수 있음
- Cat은 specialize한 Animal (Animal <- Cat)

- ![alt text](image-19.png)
- 하나의 class는 여러 개의 class 상속 가능

C++에서는 private 자식 Object를 생성하면, 메모리는 부모와 함께 할당되지만, access는 불가능
Inheritance hierarchy를 만들 때, 어떤 방식으로 만들까?
- Top Down && Bottom Up 둘다 사용

- ![alt text](image-20.png)
- Subclass 들은 부모 및 조상의 operation을 전부 물려받음
- Dog & Cat은 nurse(),sleep(),eat(),play()를 가짐
- Superclass의 특징은 SubClass의 공통된 특징

- ![alt text](image-21.png)
- Subclass는 상속된 operation을 재정의 할 수 있음 (Overriding)
- rating 이라는 operation을 상속받아서 쓰고 싶은데, 기능을 바꾸고 싶음
# **Overriding**
- - Overriding 할때는 signatures(header)을 바꾸면 안됨
- - 부모의 함수를 사용하고 싶으면 super.rating()
# **Overloading**
- - 하나의 class안에 이름이 같은 메소드를 여러 개 define
- - int add(a,b) , int add(a,b,c) 처럼 이름은 같아도 구분은 할 수 있어야 하니까 signature중 무언가를 바꿈(Type or parameter)

# Is a relation
- Student is a Person, 역은 성립하면 안됨
- 부모는 포괄적인 개념, 자식은 전문화된 개념
- **is a** relationship 강화
- - ***부모가 할 수 있는 일은 자식도 다 할 줄 알아야 함***
- - ***부모를 사용할 수 있는 곳이면, 자식이 대신 할 수 있어야 함 (LSP-Liskov Substitution Principle)***

# interface inheritance
- ![alt text](image-22.png)
- inheritance의 목적은 interface의 공유
- interface의 공유 목적으로 사용할 때는 supertype, subtype로 분류 가능

# implementation inheritance
- 코드 재사용의 목적으로 상속을 사용하는 경우도 존재
- **implemented in terms of** relationship 강화
- class inheritance 라고도 불림
- ![alt text](image-23.png)
- - Stack은 List를 활용하여 만듦
- - Stack에 있는 function만 부르려면, List를 private하게 선언

# Decide inheritance
- inheritance of function interface only
- inheritance of function interface & implementation  

# Appropriate type
- Pure virtual functon
- - interface만 상속하기 때문에, 하위 클래스에서 구현해야 함
- Virtual function
- - interface + implementation 상속, overriding 가능
- Nonvirtual function
- - interface + implementation 상속, overriding 불가능

# reference varaible types 

- static 은 선언했을 때의 type으로, 변하지 않음
- dynamic 은 실제 type으로, 바뀔 수 있음
- ![alt text](image-24.png)
- m의 static type은 Movie
- m의 dynamic type은 JamesBondMovie. Superclass <- subclass이므로 가능
- ![alt text](image-26.png)
- jm의 static type은 JamesBondMovie, 아직 dynamic type이 없는 상태
- m = jm을 했을때, Superclass <- subclass이므로 가능. 이때의 dynamic type은 jm. 컴파일러는 static type으로만 비교
- jm = m은 error 

- ![alt text](image-25.png)
- subclass는 superclass에 assigned 가능 
- A는 하위 클래스 모두 assign 가능

## Message legality
- ![alt text](image-27.png)
- ![alt text](image-28.png)
- compiler는 operation이 적합한지 static type으로 확인
- static type에서부터 root 방향으로 올라가면서 확인

- ![alt text](image-29.png)
- subclass는 superclass가 하는 일 모두 가능하지만, 역은 안됌
- 왼쪽에서는 Attraction a가 이해할 수 있는 message인지 확인
- 오른쪽에서는 A가 attraction type인지 확인

- ![alt text](image-30.png)
- message가 receiver에게 보내졌을 때, runtime에서는 dynamic type 사용
- static type은 C 지만, dynamic type은 E
- E의 h() 확인

## Compile & Run Time
- ![alt text](image-31.png)
# CompileTime
- Static or early binding - 컴파일 할때 어떤 함수 or 메소드 호출할지 결정
- Java/C++ Static function - 객체를 생성하지 않고 호출 
- C++ Non-virtual function

# Runtime
- dynamic binding or late binding - 코드가 실행될 때 어떤 함수 or 메소드 호출할지 결정
- Java/C++ Virtual function - 객체 타입에 따라 호출할 함수 결정하고, 다형성을 구현하는 데 사용
## Polymorphism
- 하나의 객체가 multi(Poly) + form(Morphism)을 가질 수 있음
- Message sender의 입장에서 receiver가 누구냐에 따라서, 다르게 행동할 수 있음

# Dynamic dispatch
- 실제는 dynamic하게 결정

