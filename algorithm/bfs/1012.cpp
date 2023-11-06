#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[51][51];
bool visit[51][51];
queue<pair<int,int>> que;
int m,n,num;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

void bfs(int i,int j){ 
    que.push({i,j});
    visit[i][j] = true;
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
            int nx = cur.first + dx[k]; 
            int ny = cur.second + dy[k];
            if(nx<0||nx>=n ||ny<0||ny>=m) continue;
            if(board[nx][ny]!=1 || visit[nx][ny]) continue;
            que.push({nx,ny});
            visit[nx][ny] = true;
        }
    }
}
int main(){
    int t;
    cin >> t;
    for(int l = 0;l<t;l++){
        int cnt = 0;
        cin >> m >> n >> num;
        for(int k=0; k<num;k++){ //배추있는 자리는 1 없는 자리는 0
            int x,y;
            cin >> y >> x;
            board[x][y] = 1;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j] == 1 && !visit[i][j]){
                    bfs(i,j);
                    cnt++;
                }
            }
        }
        cout << cnt << '\n';
        for(int i = 0; i < n; i++){
            memset(board[i],0,sizeof(int)*m);
            memset(visit[i],0,sizeof(int)*m);
        }
    }
    return 0;
}