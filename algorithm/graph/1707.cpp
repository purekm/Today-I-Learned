#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;
vector<unordered_set<int>> vec(20001);

int visit[20001];

bool bfs(int num){
    fill(visit,visit+20001,0);
    visit[num]++;
    queue<pair<int,int>> que;
    que.push({num,0});
    
    while(!que.empty()){
        int node = que.front().first;
        int parent = que.front().second;
        que.pop();
        for(int next : vec[node]){
            if(!visit[next]){
                visit[next]++;
                que.push({next,node});
            }else if(next != parent) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t,v,e;
    cin >> t;
    for(int i=0;i<t;i++){
        int v,e;
        cin >> v >> e;
        for (int j = 1; j <= v; ++j) {
            vec[j].clear();
        }
        for(int j=0;j<e;j++){
            int v1,v2;
            cin >> v1 >> v2;
            vec[v1].insert(v2);
            vec[v2].insert(v1);
        }
        bool cycle = false;
        for(int j=1;j<=v;j++){
            if(!visit[j]){
                if(bfs(i)){
                    cycle = true;
                    break;
                }
            }
        }
        if(!cycle) cout << "YES" << '\n';
        else cout << "NO" << '\n';

    }
    
    return 0;
}
