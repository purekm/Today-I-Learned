#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;
vector<unordered_set<int>> light(100);
vector<unordered_set<int>> heavy(100);
bool visit[100];

int bfs(vector<unordered_set<int>> vec,int num){
    fill(visit,visit+100,false);
    visit[num] = true;
    queue<int> que;
    que.push(num);
    int count = 0;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        for(int next : vec[cur]){
            if(visit[next]) continue;
            visit[next] = true;
            count++;
            que.push(next);
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int big,small;
        cin >> big >> small;
        light[big].insert(small);
        heavy[small].insert(big);
    }
    int result = 0;
    for(int i=1;i<=n;i++){
        int light_cnt = bfs(light,i);
        int heavy_cnt = bfs(heavy,i);
        if(light_cnt >=(n+1)/2 || heavy_cnt >=(n+1)/2) result++;
    }
    cout << result;
    return 0;
}
