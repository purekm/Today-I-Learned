#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[101][101];
int group[101][101];
bool visit[101][101];
int dist[101][101] ={-1,};
queue<pair<int,int>> que;
int n,x,y,z,island,cnt;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};


void grouping(int i,int j){ // 대륙 번호
    island++;
    group[i][j] = island;
    que.push({i,j});
    visit[i][j] = true;
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
            int nx = cur.first + dx[k]; 
            int ny = cur.second + dy[k];
            if(nx<0||nx>=n ||ny<0||ny>=n) continue;
            if(!visit[nx][ny]){
                if(board[nx][ny]==1){
                    visit[nx][ny] = true;
                    group[nx][ny] = island; // 대륙 번호
                    que.push({nx,ny});
                }
            }
        }

    }
}
int bfs(){ // 최소 거리 찾기 
    queue<pair<int,int>> queue;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(group[i][j] != 0){ //대륙이라면 dist 0, que에 push
                dist[i][j] = 0;
                queue.push({i,j});
            }
        }
    }
    int result = 10000;
    while(!queue.empty()){
        pair<int,int> cur = queue.front();
        queue.pop();
        for(int k=0;k<4;k++){
            int nx = cur.first+dx[k];
            int ny = cur.second+dy[k];
            if((nx<0||nx>=n ||ny<0||ny>=n)|| group[nx][ny] == group[cur.first][cur.second]) continue;
            if(group[nx][ny] != 0){ // 다른 대륙을 도착했을 때
                result = min(result,dist[nx][ny]+dist[cur.first][cur.second]);
            }else{ //다음 칸이 바다
                group[nx][ny] = group[cur.first][cur.second];
                dist[nx][ny] = dist[cur.first][cur.second]+1;
                queue.push({nx,ny});
            }
        }
    }
    return result;
}
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> board[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1 && !visit[i][j]) grouping(i,j);
        }
    }
    int res = bfs();
    cout << res;
    return 0;
}