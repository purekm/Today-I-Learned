## heap은 최댓값, 최솟값을 꺼낼 때 빠르기 때문에, 이와같은 유형에서 사용
## 문제 1번
import heapq
def solution(scoville, K):
    heap = []
    for i in scoville:
        heapq.heappush(heap,i)
    answer = 0
    if heap :
        while heap[0] < K and len(heap) >=2 :
            min1 = heapq.heappop(heap)
            min2 = heapq.heappop(heap)
            new_scoville = min1 + min2*2
            heapq.heappush(heap,new_scoville)
            answer = answer + 1
    
    if heap[0] < K:
        return -1
    else:
        return answer
## for문으로 heap을 구성할 경우에는 O(NlogN) 만큼 걸림. 하지만, heapify 함수를 사용하면 O(N)만큼 걸림.
## 힙을 구성하는 과정에서 한개씩 넣느냐, 아니면 한번에 구성하느냐의 차이

## 문제 2번
import heapq

def solution(jobs):
    heap = []
    jobs.sort()
    num = 0
    i = 0
    current = 0
    answer = 0
    while num < len(jobs):
        while i < len(jobs) and jobs[i][0]<=current :
            heapq.heappush(heap, (jobs[i][1], jobs[i][0])) 
            i += 1
            
        if heap:
            tasktime,requesttime = heapq.heappop(heap) 
            current += tasktime
            answer += current-requesttime
            num +=1
        else:
            current = jobs[i][0]
    answer = answer // len(jobs)
        
    
    return answer
## job들은 실제에서 요청 시점을 기준으로 정렬.
## heap에는 내가 heap에 추가할 수 있는 작업 중에서 소요 시간이 가장 작은 최소힙으로 구성해서, root를 pop 하여 작업
## i는 내가 어디까지 작업을 진행했는지 보여주는 지표로 필수적...이였다