def solution(friends, gifts):
    answer = 0
    relationship = {}
    give = {f: 0 for f in friends}
    receive = {f: 0 for f in friends}
    max_gift = 0

    # 배열 생성
    for giver in friends:
        relationship[giver] = {}
        for receiver in friends:
            relationship[giver][receiver] = 0

    for name in gifts:
        giver, recevier = name.split()
        relationship[giver][receiver] += 1
        give[giver] += 1
        receive[receiver] += 1
    
    # 각 친구가 다음 달에 받을 선물을 저장할 딕셔너리
    next_month = {f: 0 for f in friends}

    for i in range(len(friends)):
        for j in range(i + 1, len(friends)):
            p1 = friends[i]
            p2 = friends[j]
            
            # 1. 두 사람 간의 선물 기록 확인
            # p1이 p2에게 준 횟수 vs p2가 p1에게 준 횟수
            p1_to_p2 = relationship[p1][p2]
            p2_to_p1 = relationship[p2][p1]
            
            if p1_to_p2 > p2_to_p1:
                next_month[p1] += 1
            elif p1_to_p2 < p2_to_p1:
                next_month[p2] += 1
            else:
                # 2. 준 횟수가 같거나 없으면 '선물 지수' 비교
                # 선물 지수 = 준 개수 - 받은 개수
                p1_score = give[p1] - receive[p1]
                p2_score = give[p2] - receive[p2]
                
                if p1_score > p2_score:
                    next_month[p1] += 1
                elif p1_score < p2_score:
                    next_month[p2] += 1
                    
    # 3. 가장 많이 받은 사람의 선물 수 구하기
    if next_month:
        answer = max(next_month.values())

    return answer

# 친구들과 시작한 코테.. 정한 시간내에 풀진 못했음
# 테이블 형식으로 2차원 딕셔너리에 서로 주고받은 선물은 기록할 수 있었음
# 하지만 for문 부분을 작성을 못했었는데, 다음 달 받을 선물을 기준으로 조건을 그냥 맞춰서 하면 되는 거 였음..
# {f: 0 for f in friends} 이런식으로 딕셔너리를 초기화 하는 방법도 새로 알게 되었음..
# 정답 답안들을 보니 give, receive 딕셔너리를 따로 만드는 것 보다 gifts 배열로 하나로 처리하는 게 더 깔끔해보였음
