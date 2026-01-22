# 문제 1번
from collections import deque
def solution(arr):
    answer = deque()
    for i in arr:
        if answer:
            if i!=answer[-1]:
                answer.append(i)
        else:
            answer.append(i)
    return list(answer)
## 코테에서는 정답을 대부분 리스트로 하는 것을 원하기 때문에, list로 데이터 변환

# 문제 2번
from collections import deque
def solution(progresses, speeds):
    answer = []
    queue = deque()
    for i in range(len(progresses)):
        left_days = (100-progresses[i]+speeds[i]-1 )//speeds[i]
        queue.append(left_days)
    
    while queue :
        count = 1
        prev = queue.popleft()
        while queue and queue[0]<= prev:
            queue.popleft()
            count +=1
        answer.append(count)
        
    return answer
## left_days에서 올림처리를 ceil로 하는 대신 트릭 추가. A//B 에서 올림처리가 힘드니까 A+(B-1) // B로 올림처리
## python 문법에 조금 더 익숙해지기