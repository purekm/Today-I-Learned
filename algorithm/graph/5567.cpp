#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<unordered_set<int>> graph(n+1);
    unordered_set<int> result;
    result.clear();
    bool visit[501] = {false,};
    for(int i=0;i<m;i++){
        int v,e;
        cin >> v >> e;
        graph[v].insert(e);
        graph[e].insert(v);
    }
    queue<int> que;
    visit[1] = true;

    for(auto e: graph[1]) {
        result.insert(e);
        for(auto k:graph[e]){
            result.insert(k);
        }
    }
    if(result.empty()) cout << 0;
    else cout << result.size()-1;
    return 0;
}
