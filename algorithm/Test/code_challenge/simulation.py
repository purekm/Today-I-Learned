# 비밀코드해독
# 1~n

from itertools import combinations

def solution(n, q, ans):
    all_cases = list(combinations(range(1, n + 1), 5))
    answer = 0
    for case in all_cases:
        case_set = set(case)
        flag = True
        for i in range(len(q)):
            correct = len(case_set & set(q[i]))
            if correct != ans[i]:
                flag = False
                break

        if flag == True:
            answer += 1

    return answer

## python에는 combination과 set이 있다는 걸 염두해둘 것

