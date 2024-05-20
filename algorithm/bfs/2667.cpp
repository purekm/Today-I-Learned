#include <iostream>
#include <array>
#include <queue>
#include <string.h>
#include <tuple>
#include <algorithm>

using namespace std;

int n,k,num; //m,n은 세로와 가로를 나타내고, k는 block 개수, num은 0들의 집합 개수 이다.
string board[26];
int visit[26][26];
queue<pair<int,int>> que;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int flag[26*13] = {0,}; // group의 인덱스와 넓이를 나타내기 위한 배열
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
            if(nx>=n || ny>=n || nx<0 || ny<0) continue;
            if(board[nx][ny] != '1' || visit[nx][ny]) continue;
            flag[num]++; //group에 있는 0의 개수 +1
            que.push({nx,ny});
            visit[nx][ny] = true;
        }
    }
    num++; // 한 group을 모두 탐색하고 나면 다음 group을 가리키기위해 인덱스 +1
}
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> board[i];
    } 
    for(int i = 0 ; i < n ; i++) memset(visit[i], 0,sizeof(visit[i]));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!visit[i][j]&&board[i][j]=='1') bfs(i,j);
        }
    }
    sort(flag,flag+num);
    cout << num << '\n';
    for(int i=0;i<num;i++) cout << flag[i] << '\n';
    
    return 0;
}