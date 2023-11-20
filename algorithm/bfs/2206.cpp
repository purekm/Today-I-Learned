#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>

using namespace std;

int board[1001][1001];
int dist[1001][1001]={1,};
bool visit[1001][1001][2];
queue<tuple<int,int,int>> que;
int n,m,x,y,z;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

void bfs(){ 
    que.push({0,0,0});
    visit[0][0][0] = true;
    visit[0][0][1] = true;
    while(!que.empty()){
        tuple<int,int,int> cur = que.front();
        que.pop();
        tie(x,y,z) = cur;
        if(x==n-1 && y==m-1) return;
        for(int k =0;k<4;k++){ // cur의 상하좌우 탐색
            int nx = x + dx[k]; 
            int ny = y + dy[k];
            if(nx<0||nx>=n ||ny<0||ny>=m) continue;
            if(board[nx][ny]==0){
                if(!visit[nx][ny][z]){
                    que.push({nx,ny,z});
                    dist[nx][ny]=dist[x][y]+1;
                    visit[nx][ny][z]= true;
                }
            }else if(board[nx][ny]==1){
                if(!visit[nx][ny][1]&&z==0){
                    que.push({nx,ny,1});
                    dist[nx][ny]=dist[x][y]+1;
                    visit[nx][ny][1]= true;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << dist[i][j] << ' ';
            }
            cout<<'\n';
        }
        cout << '\n';
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            board[i][j] = s.at(j)-'0';
        }
    }
    bfs();
    if(board[n-1][m-1]==0){
        if(dist[n-1][m-1]==0){
            if(n==1&&m==1) cout << 1;
            else cout << -1;
        }else cout<< dist[n-1][m-1];
    }
    return 0;
}