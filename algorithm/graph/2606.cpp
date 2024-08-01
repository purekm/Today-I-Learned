#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<unordered_set<int>> graph(n+1);
    bool visit[101] = {false,};
    for(int i=0;i<m;i++){
        int v,e;
        cin >> v >> e;
        graph[v].insert(e);
        graph[e].insert(v);
    }
    queue<int> que;
    visit[1] = true;
    int cnt = 0;

    for(auto e: graph[1]) {
        que.push(e);
        visit[e] = true;
        cnt++;
    }
    while(!que.empty()){
        auto cur = que.front();
        que.pop();
        auto next = graph[cur];
        for(auto e : next){
            if(visit[e]) continue;
            que.push(e);
            visit[e] = true;
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}
