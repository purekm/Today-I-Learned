#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[101][101];
bool visit[101][101];
queue<pair<int,int>> que;
int n;
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
            if(nx<0||nx>=n ||ny<0||ny>=n) continue;
            if(board[nx][ny]!=board[cur.first][cur.second] || visit[nx][ny]) continue;
            que.push({nx,ny});
            visit[nx][ny] = true;
        }
    }
}
int main(){
    char c; //RGB 색 구분
    int cnt = 0,cnt2 = 0; 
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> c;
            if(c=='R') board[i][j]=1;
            else if(c=='G') board[i][j]=2;
            else board[i][j]=3;
        }        
    }
    for(int i=0;i<n;i++){ //적록색약 아닌 사람이 봤을때
        for(int j=0;j<n;j++){
            if(!visit[i][j]){
                bfs(i,j);
                cnt++;
            }
        }
    }
    for(int i=0;i<n;i++) memset(visit[i],0,sizeof(int)*n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==2) board[i][j] =1;
        }
    }
    for(int i=0;i<n;i++){ //적록색약 인 사람이 봤을때
        for(int j=0;j<n;j++){
            if(!visit[i][j]){
                bfs(i,j);
                cnt2++;
            }
        }
    }
    
    cout << cnt <<" "<<cnt2;
    return 0;
}