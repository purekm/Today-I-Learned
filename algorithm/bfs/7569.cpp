#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>

using namespace std;

int board[101][101][101];
queue<tuple<int,int,int>> que;
int n,m,h,x,y,z;
int day;
int dx[6] = {1,0,-1,0,0,0};
int dy[6] = {0,1,0,-1,0,0};
int dh[6] = {0,0,0,0,1,-1};


void bfs(){ 
    day = 0;
    while(!que.empty()){
        int size = que.size();
        day++;
        for(int l=0; l<size;l++){
            tuple<int,int,int> cur = que.front();
            tie(x,y,z) = cur;
            que.pop();
            for(int k =0;k<6;k++){ // cur의 상하좌우 탐색
                int nx = x + dx[k]; 
                int ny = y + dy[k];
                int nh = z + dh[k];
                if(nx>=0&&nx<n&&ny>=0&&ny<m&&nh>=0&&nh<h&&board[nh][nx][ny]==0){
                    que.push({nx,ny,nh});
                    board[nh][nx][ny] = 1;
                }
            }
        }
    }
}
int main(){
    cin >> m >> n >> h;
    for(int k=0;k<h;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin >> board[k][i][j];
                if(board[k][i][j]== 1) que.push({i,j,k}); 
            }
        }
    }
    bfs();

    for(int k=0;k<h;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[k][i][j]==0){
                    cout << -1;
                    return 0;
                }
            }
        }
    }
    cout << day-1; // 마지막에  bfs에서 while문 한번 더 돌아서 -1;
    return 0;
}