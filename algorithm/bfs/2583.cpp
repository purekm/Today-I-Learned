#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>
#include <algorithm>

using namespace std;

int m,n,k,num; //m,n은 세로와 가로를 나타내고, k는 block 개수, num은 0들의 집합 개수 이다.
int board[101][101];
int visit[101][101];
queue<pair<int,int>> que;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int flag[5000] = {0,}; // group의 인덱스와 넓이를 나타내기 위한 배열
void bfs(int x, int y){
    flag[num]++; // x,y 자리 더해주기
    visit[x][y] = true;
    que.push({x,y});
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int i=0;i<4;i++){
            int nx = cur.first+dx[i];
            int ny = cur.second+dy[i];
            if(board[nx][ny] != 0 || visit[nx][ny]) continue;
            if(nx>=m || ny>=n || nx<0 || ny<0) continue;
            flag[num]++; //group에 있는 0의 개수 +1
            que.push({nx,ny});
            visit[nx][ny] = true;
        }
    }
    num++; // 한 group을 모두 탐색하고 나면 다음 group을 가리키기위해 인덱스 +1
}
int main(){
    cin >> m >> n >> k;
    num = 0;
    for(int i = 0 ; i < m ; i++) memset(visit[i], 0,sizeof(visit[i]));
    
    for(int l=0;l<k;l++){
        int lx,ly,ux,uy;
        cin >> lx >> ly >> ux >> uy;
        for(int i=ly;i<uy;i++){
            for(int j=lx;j<ux;j++){
                board[i][j]++;
            }
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!visit[i][j] && board[i][j]==0){ // group에서 첫 번째칸을 bfs로 탐색하여 이어져있는 모든 0을 탐색
                bfs(i,j);
            }
        }
    }
    sort(flag,flag+num); 
    cout << num << '\n';
    for(int i=0;i<num;i++){
        cout << flag[i] << " ";
    }
    
    return 0;
}