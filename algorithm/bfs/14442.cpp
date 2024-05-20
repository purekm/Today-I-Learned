#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>
#define MAX 1001
using namespace std;

char board[MAX][MAX];
int visit[11][MAX][MAX];
int dist[11][MAX][MAX];
queue<tuple<int,int,int>> que;
int n,m,k,x,y,z;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

void bfs(){ 
    while(!que.empty()){
        tuple<int,int,int> cur = que.front();
        tie(x,y,z) = cur;
        que.pop();
        if(x == n-1 && y == m-1) return; // 마지막 자리에 도달하면 bfs종료
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            int nz = z + 1;
            if(nx>=n||ny>=m||nx<0||ny<0) continue;
            if(board[nx][ny]=='1'&&z<k&&!visit[nz][nx][ny]){ //벽을 깰 기회가 있고, 방문하지 않았으며, 다음 칸이 1인 경우
                que.push({nx,ny,nz}); // z++를 push해줌
                visit[nz][nx][ny]= true;
                dist[nz][nx][ny] = dist[z][x][y]+1;
            }
            else if(board[nx][ny]=='0' && !visit[z][nx][ny]){ //다음 벽이 0인 경우
                que.push({nx,ny,z}); 
                visit[z][nx][ny] = true;
                dist[z][nx][ny] = dist[z][x][y]+1; 
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << dist[z][i][j] << ' ';
            }
            cout<<'\n';
        }
        cout << '\n';
    }
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for(int i = 0 ; i < n ; i++) memset(visit[i], false, sizeof(visit[i]));
    for(int i = 0 ; i < 11; i++) {
        for(int j = 0 ; j < MAX ; j++) {
            fill(dist[i][j], dist[i][j] + MAX, 0);
        }
    }
    cin >> n >> m >> k;

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) {
            cin >> board[i][j];
        }
    }
    que.push({0,0,0});
    visit[0][0][0] = true;
    dist[0][0][0] = 1;
    bfs();
    if(dist[z][n-1][m-1]==0) cout << -1;
    else cout << dist[z][n-1][m-1];
    
    return 0;
}