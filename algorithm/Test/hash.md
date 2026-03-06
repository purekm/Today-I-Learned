## 왜 해시를 사용하지에 대한 고민부터 해보자면 압도적인 검색 속도. 키를 활용한 검색으로 중복도 없으며, 상당히 빠름


# 문제 1번
def solution(participant, completion):
    hash_dic = {}
    for name in completion:
        hash_dic[name] = hash_dic.get(name,0)+1
        
    for name in participant:
        if hash_dic.get(name,0) == 0:
            return name
        hash_dic[name] -= 1
# 예외 상황을 생각했을 때, 예외처리가 되어있는 get함수를 활용할 것. 
# 만약 아래의 for문처럼 확실하다면 그냥 접근해도 무방함

# 문제 2번
def solution(nums):
    pokemon = {}
    for i in nums:
        pokemon[i] = 1
    
    num = len(pokemon)
    
    if num > len(nums)//2 :
        answer = len(nums)//2
    else:
        answer = num
    return answer
# 난 비교를 이렇게 진행했지만, max=len(nums)//2로 설정한 후, answer=min(num,max)로 가능

# 전화번호 문제
def solution(phone_book):
    hash_dic = {}
    for num in phone_book:
        hash_dic[num] = True
        
    for num in hash_dic:
        temp = ""
        for char in num:
            temp += char
            if temp in hash_dic and temp != num:
                return False
        
    return True
## 여기서 hash를 안 썼으면 for num in phone_book을 검사할 때 100만, temp in hash_dic 할때 100만으로 시간초과가 발생함. 이걸 방지하기 위해 hash 사용

# 의상문제
def solution(clothes):
    answer = 0
    hash_dic = {}
    length = len(clothes)
    for name, kind in clothes:
        hash_dic[kind] = hash_dic.get(kind, 0) + 1
    
    answer = 1
    for kind in hash_dic:
        answer *= hash_dic[kind]+1
    answer -= 1
        
    return answer

## 옷은 안 입는 선택지때문에 +1한 선택지로 곱했고, 모두 안 입으면 안되니까 마지막에 -1 해줌