#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

char board[1001][1001];
bool visit[1001][1001];
queue<pair<int,int>> que;
queue<pair<int,int>> fireque;


int t,w,h;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int bfs(){ 
    int sec = 0;
    while(!que.empty()){
        sec++;
        int fqsize = fireque.size(); //불 먼저 움직이기
        for(int j=0;j<fqsize;j++){
            pair<int,int> fcur = fireque.front();
            fireque.pop();
            for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
                int nx = fcur.first + dx[k]; 
                int ny = fcur.second + dy[k];
                if(nx<0||nx>=h ||ny<0||ny>=w) continue;
                if(board[nx][ny]!='.') continue;
                fireque.push({nx,ny});
                board[nx][ny]='*';
                
            }
        }
        int size = que.size(); //상근이 움직이기
        for(int i=0;i<size;i++){
            pair<int,int> cur = que.front();
            que.pop();
            for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
                int nx = cur.first + dx[k]; 
                int ny = cur.second + dy[k];
                if(nx<0||nx>=h ||ny<0||ny>=w) return sec;
                if(board[nx][ny]=='.'&&!visit[nx][ny]){
                    que.push({nx,ny});
                    visit[nx][ny] = true;
                    board[nx][ny]='@';
                }
            }
        }
    }
    return -1;
}
int main(){
    cin >> t;
    for(int k=0;k<t;k++){
        cin >> w >> h;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cin >> board[i][j];
                if(board[i][j]=='@') {
                    visit[i][j]= true;
                    que.push({i,j});
                }
                else if(board[i][j]=='*') fireque.push({i,j});
            }
        }
        int result = bfs();
        if(result==-1) cout<<"IMPOSSIBLE"<<'\n';
        else cout << result<<'\n';
        for(int i=0;i<h;i++){
            memset(visit[i],0,sizeof(visit[i]));
            memset(board[i],'.',sizeof(board[i]));
            while(!que.empty()) que.pop();
            while(!fireque.empty()) fireque.pop();
        }
    }
    return 0;
}