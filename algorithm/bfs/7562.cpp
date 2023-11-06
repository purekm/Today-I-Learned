#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[301][301];
bool visit[301][301];
int dist[301][301] ={0,};
queue<pair<int,int>> que;
int t,n,s1,s2,l1,l2;
int dx[8] = {1,2,1,2,-1,-2,-1,-2};
int dy[8] = {2,1,-2,-1,2,1,-2,-1};

void bfs(int i,int j){ 
    que.push({i,j});
    visit[i][j] = true;
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int k =0;k<8;k++){ // cur의 상하좌우 탐색
            int nx = cur.first + dx[k]; 
            int ny = cur.second + dy[k];
            if(nx<0||nx>=n ||ny<0||ny>=n) continue;
            if(visit[nx][ny]) continue;
            que.push({nx,ny});
            visit[nx][ny] = true;
            dist[nx][ny] = dist[cur.first][cur.second]+1;
        }
    }
}
int main(){
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n >> s1 >> s2 >> l1 >> l2;
        bfs(s1,s2);
        cout << dist[l1][l2]<<'\n';
        for(int j=0;j<n;j++) { //bfs 한번 하고 초기화
            memset(dist[j],0,sizeof(int)*n);
            memset(visit[j],0,sizeof(int)*n);

        }
    }

    return 0;
}