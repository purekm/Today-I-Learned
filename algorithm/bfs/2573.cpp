#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[301][301];
bool visit[301][301];
queue<pair<int,int>> que;
int m,n,cnt;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

void bfs(int i,int j){ 
    visit[i][j] = true;
    que.push({i,j});
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
            int nx = cur.first + dx[k]; 
            int ny = cur.second + dy[k];
            if(nx<0||nx>=n ||ny<0||ny>=m) continue;
            if(visit[nx][ny]) continue;
            if(board[nx][ny]==0){
                if(board[cur.first][cur.second]>0){
                    board[cur.first][cur.second]--;
                }else{
                    board[cur.first][cur.second]=0;
                }
            } 
            else {
                que.push({nx,ny});
                visit[nx][ny] = true;
            }
        }
    }
    
    return;
}
int main(){
    cin >> n >> m;
    int year = 0;
    cnt = 0;
    int prev_cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> board[i][j];
        }
    }
    while(true){
        cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0; j<m;j++){
                if(board[i][j] != 0 && !visit[i][j]){
                    bfs(i,j);
                    cnt++;
                }
            }
        }
        if(cnt >= 2) break;
        if(cnt == 0 && cnt == prev_cnt) {
            year = 0;
            break;
        }
        year++;
        prev_cnt = cnt;
        for(int i=0;i<n;i++){
            memset(visit[i],0,sizeof(visit[i]));
        }

    }
    cout << year;


    return 0;
}