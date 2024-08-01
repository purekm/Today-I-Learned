#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;
bool visit[51];
int candidate[51];
vector<unordered_set<int>> vec(51);

int n;

int bfs(int num){
    fill(visit,visit+51,false);
    visit[num] = true;
    queue<pair<int,int>> que;
    int stage = 0;
    que.push({num,0});
    while(!que.empty()){
        auto cur = que.front();
        int now = cur.first;
        int nowstage = cur.second;
        que.pop();
        if(stage<nowstage) stage = nowstage;
        for(auto e : vec[now]){
            if(visit[e]) continue;
            visit[e] = true;
            que.push({e,nowstage+1});
        }
    }
    return stage;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int x,y;
    int Min = 1000000;
    int MinCandidates = 1;
    while(true){
        cin >> x >> y;
        if(x==-1 && y ==-1) break;
        vec[x].insert(y);
        vec[y].insert(x);
    }
    for(int i=1;i<=n;i++){
        int result = bfs(i);
        candidate[i] = result;
        if(Min > result){
            MinCandidates = 1;
            Min = result;
        }else if(Min == result){
            MinCandidates++;
        }
    }
        cout << Min << " " << MinCandidates << '\n';
    for(int i=1;i<=n;i++) 
        if(Min == candidate[i]) cout << i << " ";
    return 0;
}
