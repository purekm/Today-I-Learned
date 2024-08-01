#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;
bool visit[101][101];
vector<unordered_set<int>> vec(101);

void dfs(int x,int y){
    for(auto e:vec[x]){
        if(visit[y][e]) continue;
        visit[y][e] = true;
        dfs(e,y);
    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int num;
            cin >> num;
            if(num) {
                vec[i].insert(j);
            }
        }
        
    }
    for(int i=0;i<n;i++){
        dfs(i,i);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << visit[i][j] << " ";
        }
        cout << '\n';
    }
    

    return 0;
}
