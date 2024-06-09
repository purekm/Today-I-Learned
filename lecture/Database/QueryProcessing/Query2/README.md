SQL 쿼리의 결과는 정렬이 필요할 수 있다.<br/>
입력 릴레이션이 정렬된 경우 쿼리 처리 효율이 향상<br/>
정렬 방법<br/>
1. 정렬 키에 인덱스 생성<br/>
   1. 정렬 키에 인덱스를 생성하고 이를 사용하여 정렬된 순서로 릴레이션을 읽는다. 레코드에 대해 한번의 디스크 블록 access를 초래할 수 있음<br/>
2. 메모리에 적합한 릴레이션의 경우<br/>
   1. 퀵소트 같은 기술 사용 가능. 릴레이션이 메모리에 적합하지 않은 경우가 많음<br/>
3. 메모리에 적합하지 않은 릴레이션의 경우<br/>
   1. External Sort-Merge가 좋은 선택<br/>


정렬된 Run 만들기<br/>
데이터를 메모리에 읽어들여 부분적으로 정렬된 런 생성<br/>
각 런을 파일에 저장하고 이 과정을 반복.<br/>
총 런의 수를 계산하고, 다음 단계인 병합으로 이동<br/>
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/a9e63b19-aafb-49f0-b885-0078ce112ac6)
![image](https://github.com/purekm/Today-I-Learned/assets/90774046/1e671551-2af3-4f30-9f88-5ae00b93baa7)

