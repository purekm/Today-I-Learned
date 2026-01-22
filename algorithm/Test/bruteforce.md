## 문제 1번
def solution(sizes):
    answer = 0
    max_x = 0
    max_y = 0
    for x,y in sizes:
        if x<y:
            x,y = y,x
        max_x = max(max_x,x)
        max_y = max(max_y,y)
            
    answer = max_y*max_x
    return answer

## 문제 2번
def solution(answers):
    answer = []
    solver1 = [1,2,3,4,5]
    solver2 = [2,1,2,3,2,4,2,5]
    solver3 = [3,3,1,1,2,2,4,4,5,5]
    score1 = 0
    score2 = 0
    score3 = 0
    num = 0
    for i in answers:
        if i == solver1[num%len(solver1)]:
            score1 +=1
        if i == solver2[num%len(solver2)]:
            score2 +=1
        if i == solver3[num%len(solver3)]:
            score3 +=1
        num +=1 
    max_score = max(max(score1,score2),score3)
    result =[]
    if max_score == score1:
        result.append(1)
    if max_score == score2:
        result.append(2)
    if max_score == score3:
        result.append(3)
    
    return result
