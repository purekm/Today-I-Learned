#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int board[5][5][5];
int newboard[5][5][5];
int dist[5][5][5];
bool check[5];
int dx[6] = {1,-1,0,0,0,0};
int dy[6] = {0,0,1,-1,0,0};
int dz[6] = {0,0,0,0,1,-1};
int min=100;
void turn(int n,int level, int mod) {
    if (mod == 0) {
        for(int i = 0 ; i < 5 ; i++) {
            for(int j = 0 ; j < 5; j++){
                newboard[level][i][j] = board[n][i][j];
            }
        }
    }
    else if(mod == 1) { // 90 도 
        for(int i = 0 ; i < 5 ; i++) {
            for(int j = 0 ; j < 5; j++){
                newboard[level][j][5-1-i] = board[n][i][j];
            }
        }
    }
    else if (mod == 2) {
        for(int i = 0 ; i < 5 ; i++) {
            for(int j = 0 ; j < 5; j++){
                newboard[level][5-1-i][5-1-j] = board[n][i][j];
            }
        }
    }
    else {
        for(int i = 0 ; i < 5 ; i++) {
            for(int j = 0 ; j < 5; j++){
                newboard[level][5-1-j][i] = board[n][i][j];
            }
        }
    }
}
 
int BFS(){
    int start = newboard[0][0][0];
    int cnt = 0;
    if(!start) return 0;
    queue<tuple<int,int,int>> que;
    que.push({0,0,0});
    dist[0][0][0] ++;
    while(!que.empty()){
        tuple<int,int,int> cur = que.front();
        tie(x,y,z) = cur;
        que.pop();
        for(int i=0;i<6;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            if (nx<0 || ny<0 || nz<0 || nx>=5 || ny>=5 || nz>=5) continue;
            if(newboard[nx][ny][nz]==0||dist[nx][ny][nz]!=-1) continue;
            que.push({nx,ny,nz});
            dist[nx][ny][nz] = dist[x][y][z]+1;
            if(nx==4&&ny==4&&nz==4) cnt = dist[nx][ny][nz];
        }
    }
    for(int i = 0 ; i < 5; i++ ){
        for(int j = 0 ; j < 5 ; j++) fill(dist[i][j], dist[i][j] + 5, -1);
    }
    return cnt;
}

void dfs(int level){
    if(level == 5){
        int minimum = bfs();
        if(minimun>0 && minimum < min) min = minimum;
        return;
    }
    for(int i=0;i<5;i++){
        if(!check[i]){
            check[i] = true;
            for(int j=0;j<4;j++){
                turn(i,level,j);
                dfs(level+1);
            }
            check[i] = false;
        }
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            for(int h=0;h<5;h++) cin >> board[i][j][h];
        }
    }
    dfs(0);
    if(min==100) cout << -1;
    else cout << min;

    return 0;

}