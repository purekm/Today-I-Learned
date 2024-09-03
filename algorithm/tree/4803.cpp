#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
bool visit[501] = {false};
vector<vector<int>> node;
bool dfs(int num,int prev){
    visit[num] = true;
    for(auto e : node[num]){
        int next = e;
        if(next == prev) continue;
        if(visit[next]) return false;
        if(!dfs(next,num)) return false;
    }
    return true;
}
void initialize(int n) {
    node = vector<vector<int>>(n + 1, vector<int>(0));
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t=0;
    while(true){
        int n,m, tree = 0;
        cin >> n >> m;
        t++;
        if(n==0 && m ==0) break;
        initialize(n);
        fill(visit,visit+501,false);
        for(int i=0;i<m;i++){
            int e1,e2;
            cin >> e1 >> e2;
            node[e1].push_back(e2);
            node[e2].push_back(e1);
        }
        for(int i=1;i<=n;i++){
            if(visit[i]) continue;
            if(dfs(i,0)) tree++;
        }
        if(tree == 0) cout << "Case " << t << ": No trees.\n";
        else if(tree == 1) cout << "Case " << t << ": There is one tree.\n";
        else cout << "Case " << t << ": A forest of " << tree <<" trees.\n";
    }
    
    return 0;
}
