Indexing 4
B+- tree organization<br/> 
Space utilization 을 위해 sibling을 더 많이 포함하는 것이 좋다<br/> 
B+트리에서 node를 split하는 것은 비용이 비싸다. <br/> 
1.	Secondary index가 pointer대신에 search key를 저장하면 됨<br/>
2.	만약 search key가 non unique 하다면 unique한 record만 저장<br/>
3.	추가적인 traversal이 필요하기 때문에 queries 에는 비싸지만, split에는 싸다<br/> 

split이나 merge를 할 때 space utilization을 기준으로 사용한다. (pointer의 개수 X)<br/> 
String이 길어질 수 있음<br/> 
1. Fanout 작아지고 Tree height 증가<br/>
    1. Look up 시간이 증가하므로 느려짐 <br/> 
2. Solution 으로 Prefix compression – 문자열의 앞부분만 사용하여 구분<br/>

Bulk loading – 많은 수의 엔트리를 인덱스에 한번에 집어넣음<br/> 
1. 랜덤하게 엔트리가 삽입되어 있으면 비효율적<br/>
2. Efficient alternative 1 (Sort)<br/>
   1. 단점으로는 leaf 노드들이 절반만 찬다.<br/> 
3. Efficient alternative 2 (Bottom-up)<br/>
   1. entry들을 sort해줌<br/>
   2. leaf 노드부터 만듦 -> space 절약 미쳤음<br/>
			
Indexing on flash<br/> 

Flash storage에 B+트리 저장 가능<br/> 
1. Look up 속도가 significantly 하게 증가<br/>
2. Magnetic disk 보다 random I/O가 빠름<br/>
3. Node size를 flash size처럼 줄여서 만들면 I/O를 절약 가능 <br/>
4. Bottom up B+트리도 좋음 (page erase가 ssd에선 필요한데, bottom up 쓰면 절약)<br/>
5. B+tree에서 erase 횟수를 줄이는 여러가지 방법들이 존재<br/>
   1. Internal node에서 buffer을 두고 update를 먼저 저장하고, 나중에 leaf에 업뎃<br/>
   2. LSM tree <br/>
6. B+tree 인덱싱의 경우에 메인 메모리에 data를 인덱스할 때 사용 가능<br/>
7. 최적화 가능<br/>
   1. 앞에서 말한 것 처럼 sibling을 많이 사용<br/> <br/>
   2. Node size를 줄여서 cache miss를 최소화 할 수 있음<br/>
   3. 큰 데이터를 가지고 있으면 메모리에 다 안 들어갈 수 있는데, 큰 데이터를 트리 형식으로 구조화 해서 look up 할 수 있게 만들면 cache miss를 최소화<br/>
   
Static Hashing<br/> 
Hash function을 사용하여 특정  bucket에 entry에 작업 가능(bucket은 하나 이상의 엔트리를 담고있음)<br/> 
Hash function은 search-key value를 받아서 bucket의 주소를 반환해주는 함수<br/> 
Static hashing – bucket의 수가 고정<br/> 
Dynamic hashing – bucket의 수가 고정되지 않음<br/> 
Hash Collision – 다른 search-key value에 Hash function을 적용했을 때 같은 결과가 나오는 경우 발생 -> 같은 bucket에 저장된 것임<br/> 
Bucket Overflow – 중복된 entry가 있을 수 있고, distribution이 적은 수의 bucket에 집중되어 있으면 overflow 발생가능 -> overflow bucket을 만들어서 거기에 저장<br/> 
Bucket overflow를 줄일 순 있지만  제거하는 것은 불가능<br/> 
Overflow chaining을 사용하는 경우 closed addressing이라고 부른다.<br/> 
 ![그림1](https://github.com/purekm/Today-I-Learned/assets/90774046/4880827c-eb36-4ebf-92a9-27fafbe2bef4)<br/> 

Static Hashing 에서는 bucket의 숫자를 적절히 정해야함<br/> 
One solution – Static Hashing을 주기적으로 rebuilding을 해준다.<br/> 
1. 비용이 비싸다.<br/>

Another solution – Dynamic hashing<br/> 
1. Linear Hashing<br/> <br/>
2. Extendable Hashing 자세히 설명 X<br/>

Ordered Indexing 과 Hashing의 차이<br/> 
Hashing은 특정한 값을 가지는 search key를 찾는 게 유리하다 Hash function 때문에<br/> 
Ordered indexing은 range queries에서 좋음<br/> 
Hash index는 주로 사용하지 않음<br/> 
Postgresql – hash index 있지만 안씀<br/> 
Oracle – static hash 는 지원, hash index는 지원X<br/> 
SQL server – B+ tree만 지원<br/> 
