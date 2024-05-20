#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>

using namespace std;

int m,n,day; //m,n은 가로와 세로를 나타내고 day는 최소 날짜
int board[1001][1001];
int visit[1001][1001];
queue<pair<int,int>> que;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

void bfs(){ 
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int i=0;i<4;i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx>=n||ny>=m||nx<0||ny<0) continue;
            if(visit[nx][ny] != -1 || board[nx][ny]!=0) continue;
            visit[nx][ny] = visit[cur.first][cur.second]+1;
            board[nx][ny] = 1;
            que.push({nx,ny});
            day = max(day,visit[nx][ny]);
            
        }
    }
}
int main(){
    cin >> m >> n;
    day = 0;
    bool check = true;
    for(int i = 0 ; i < n ; i++) memset(visit[i], -1,sizeof(visit[i]));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) {
            cin >> board[i][j];
            if(board[i][j]==1) {
                que.push({i,j});
                visit[i][j]++;
            }
        }
    }
    bfs();
   
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            if(board[i][j]==0){
                check = false;
                break;
            }
        }
    }
   
    if(check) cout << day;
    else cout << -1;
    return 0;
}