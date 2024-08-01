#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int arr[9][9];
bool visit[9][9];
int result,n,m;
int bfs(){
    int cnt = 0;
    int copy[9][9];
    queue<pair<int,int>> que;
    fill(visit[0],visit[9],0);

    for(int i=0;i<n;i++){ //que에 바이러스 위치 넣어주기 + copy배열 만들기
        for(int j=0;j<m;j++){
            copy[i][j] = arr[i][j];
            if(copy[i][j]==2){
                que.push({i,j});
                visit[i][j] = true;
            }
        }
    }
    while(!que.empty()){
        auto cur = que.front();
        que.pop();
        for(int k=0;k<4;k++){
            int nx = cur.first + dx[k];
            int ny = cur.second + dy[k];
            if(nx>=n||nx<0||ny>=m||ny<0) continue;
            if(visit[nx][ny] || copy[nx][ny] != 0) continue;
            visit[nx][ny] = true;
            copy[nx][ny] = 2;
            que.push({nx,ny});
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(copy[i][j]==0) cnt++;
        }
    }
    return cnt;
}
void dfs(int count){
    if(count == 3) {
        result = max(result,bfs());
        return;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(arr[i][j]==0){
                arr[i][j] = 1;
                dfs(count+1);
                arr[i][j] = 0;
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> arr[i][j];
        }
    }
    dfs(0);
    cout << result;
    return 0;
}