#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>

using namespace std;

int board[201][201];
int dist[201][201][31]={0,};
queue<tuple<int,int,int>> que;
int w,h,jump,x,y,z;
int dx[12] = {1,0,-1,0,-2,-2,-1,-1,1,1,2,2};
int dy[12] = {0,1,0,-1,1,-1,2,-2,2,-2,1,-1};

int bfs(){ 
    que.push({0,0,0});
    dist[0][0][0] = 0;
    while(!que.empty()){
        tuple<int,int,int> cur = que.front();
        que.pop();
        tie(x,y,z) = cur;
        if(x==h-1&&y==w-1) return dist[x][y][z];
        for(int k =0;k<12;k++){ // cur의 상하좌우 탐색
            int nx = x + dx[k]; 
            int ny = y + dy[k];
            if(nx<0||nx>=h ||ny<0||ny>=w) continue;
            if(dist[nx][ny][z]) continue;
            if(board[nx][ny] == 1) continue;
            if(k>=4){
                if(dist[nx][ny][z+1]) continue;
                if(z>=jump) continue;
                dist[nx][ny][z+1] = dist[x][y][z]+1;
                que.push({nx,ny,z+1});
            }else{
                dist[nx][ny][z] = dist[x][y][z]+1;
                que.push({nx,ny,z});

            }
        }
    }
    return -1;
}
int main(){
    cin >> jump >> w >> h;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cin >> board[i][j];
        }
    }
    cout << bfs();

    return 0;
}