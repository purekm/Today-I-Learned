#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>

using namespace std;

int r,c,cnt;
char board[1001][1001];
bool visit[1001][1001]; // 불 또는 지훈이 방문했는지 check
queue<pair<int,int>> jque; //지훈이의 위치 que
queue<pair<int,int>> fque; //불의 위치 que
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int bfs(){
    while(!jque.empty()){
        cnt++; // 불과 지훈이가 한번씩 움직였을 때 시간
        int fsize = fque.size(); // 불이 여러 개 있을 때의 상황을 고려하여 for문
        for(int i=0;i<fsize;i++){ 
            pair<int,int> fcur = fque.front();
            fque.pop();
            for(int k=0;k<4;k++){
                int nx = fcur.first + dx[k];
                int ny = fcur.second + dy[k];
                if(nx<0||ny<0||nx>=r||ny>=c) continue; // 다음 위치가 범위를 넘어가지 않으면 continue
                if(board[nx][ny] != '.'||visit[nx][ny]) continue; // 다음 위치가 '.' 이 아니거나 이미 방문한 곳이면 continue
                fque.push({nx,ny}); // 다음 불의 위치 push
                board[nx][ny] = 'F'; // 불이 방문한 장소는 'F'로 변경
                visit[nx][ny] = true; // 불이 방문했기 때문에 true로 변경
            }
        }
        int jsize = jque.size();
        for(int i=0;i<jsize;i++){ // 지훈이가 여러 위치에 있는 것을 고려함
            pair<int,int> cur = jque.front();
            jque.pop();
            for(int k=0;k<4;k++){
                int nx = cur.first + dx[k];
                int ny = cur.second + dy[k];
                if(nx<0||ny<0||nx>=r||ny>=c) return cnt; // 다음 지훈이의 위치가 보드의 범위를 넘어가면 탈출! 몇분만에 탈출했는지 cnt 반환
                if(board[nx][ny] != '.'|| visit[nx][ny]) continue;// 다음 위치가 '.' 이거나 방문한 장소면 continue
                jque.push({nx,ny}); // 다음 지훈의 위치 push
                board[nx][ny] = 'J'; // 다음 위치를 'J'로 변경
                visit[nx][ny] = true; // 방문했으므로 true
            }
        }
    }
    return -1;
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> r >> c;
    cnt = 0;
    for(int i = 0 ; i < r ; i++) memset(visit[i],false,sizeof(visit[i]));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin >> board[i][j];
            if(board[i][j]=='J'){ // J를 만났으면 jque에 push
                jque.push({i,j}); 
                visit[i][j] = true;
            }else if(board[i][j]=='F') { // F를 만났으면 fque에 push
                fque.push({i,j});
                visit[i][j] = true;
            }
        }
    }
    int result = bfs();
    if(result == -1) cout << "IMPOSSIBLE";
    else cout << result;
    return 0;
}