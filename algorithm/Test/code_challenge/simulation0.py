## 유연근무제

def solution(schedules, timelogs, startday):
    answer = 0
    for i in range(len(schedules)):
        flag = True
        day = startday
        timeline = schedules[i]+10
        if timeline % 100 >= 60:
            timeline = timeline+40
        for j in range(7):
            if day == 6 or day == 7: # 주말은 패스
                day = day%7 +1
                continue
            
            if timelogs[i][j] > timeline:
                flag = False
                break;
            day = day%7 +1
        if flag == True:
            answer += 1
            
    return answer