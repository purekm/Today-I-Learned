## 문제1번
def solution(array, commands):
    answer = []
    for start, end, k in commands:
        test = array[start-1:end]
        test.sort()
        answer.append(test[k-1])
    return answer
## 충격적이게도.. 파이썬에는 리스트 언팩킹기능이 있음. 
## commands는 이차원배열인데, 각각의 요소 3개를 한번에 꺼냄으로써 하나의 리스트를 가지고 나오는 것. 
## ex) commands=[[2,5,3],[2,1,4]] 라고 하면 2,5,3을 한번에 꺼내서 참조하고, 다음 요소인 [2,1,4]를 참조하는 것

## 문제2번
def solution(numbers):
    answer = ''
    nums=[]
    for i in numbers:
        nums.append(str(i))
    nums.sort(key=lambda x: x*3, reverse=True)
    answer = "".join(nums)
    if answer[0] =='0':
        return '0'
    return answer

# 첫자리가 가장 큰 수를 기준으로 정렬, 이때 2번째,3번째 자리수도 큰 걸 해야하는데, 1000이하의 숫자니까 문자열을 3번 곱해서 사전순으로 높은 숫자를 기준으로 정렬
# 만약 숫자가 000이면 0이 나와야하니까 예외처리
# for문으로 문자열을 더하는 것 보다 join을 사용하는 게 더 좋다고 함(메모리효율을 봤을 때 한번만 복사해서 O(N))
