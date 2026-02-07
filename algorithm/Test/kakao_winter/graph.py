# 도넛과 막대 그래프
def solution(edges):
    answer = []
    in_line = {}  
    out_line = {} 
    max_node = 0
    
    for i, j in edges:
        in_line[j] = in_line.get(j, 0) + 1
        out_line[i] = out_line.get(i, 0) + 1
        max_node = max(max_node, i,j)
    donut = 0
    stick = 0
    graph = 0
    node_num = 0
    for i in range(1,max_node+1):
        in_cnt = in_line.get(i, 0)  
        out_cnt = out_line.get(i, 0)
        
        if out_cnt >= 2 and in_cnt == 0:
            node_num = i
        elif out_cnt == 0 and in_cnt >= 1: # 정점에서 줄수도 있지않나.. 1 -> 1이상
            stick += 1
        elif out_cnt == 2 and in_cnt >= 2: # 위와 같음
            graph += 1
    total = out_line.get(node_num,0)
    donut = total-stick-graph
    answer.append(node_num)
    answer.append(donut)
    answer.append(stick)
    answer.append(graph)
    return answer

# 이 문제의 킥은.. 그래프를 판별하는 방법
# 싸이클이면 도넛. >  나가는거 1개 들어오는거 1개
# 싸이클이 아니면 막대 > 나가는거 1개만 
# 8자모양 >  2개 2개인 노드 개수를 구하기 
# 정점은 나가는거 2개 이상, 들어오는거 X
# 위와 같은 식으로 간단하게 정의할 수 있는데 문제가 1개 발생함
# 도넛과 8자의 정점을 어떻게 구분하는가..!

# 문제를 보면 임의의 정점은 모든 그래프에 연결되기때문에 그래프의 총 개수를 알 수 있음
# 도넛 or 8자를 구하면 되는데, 8자는 구하는 방식이 쉬움
# 도넛 = 전체 그래프 개수 - 막대 개수 - 8자 개수

# 마지막으로 append는 리스트로 간단하게 변  환하는게.. 좋을 것 같긴함..
 

