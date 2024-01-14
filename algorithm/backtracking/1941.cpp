#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>

using namespace std;
int n;
int result= 0;
char board[6][6];
bool check[6][6];//지나갔나?
bool visit[6][6];
bool sel[26];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
bool bfs(){
    for(int i=0; i<5;i++){
        memset(visit[i],0,sizeof(visit[i]));
        memset(check[i],0,sizeof(check[i]));
    }
    int x,y;
    for(int i=0;i<25;i++){
        if(!sel[i]) continue;
        y = i/5;
        x = i%5;
        check[y][x] = true;
    }
    queue<pair<int,int>> que;
    que.push({y,x});
    visit[y][x] = true;
    int num = 1;
    while(!que.empty()){
        int nowy = que.front().first;
        int nowx = que.front().second;
        que.pop();
        for(int k=0;k<4;k++){
            int nx = nowx+dx[k];
            int ny = nowy+dy[k];
            if(nx<0||nx>=5||ny<0||ny>=5) continue;
            if(visit[ny][nx]) continue;
            if(check[ny][nx]){
                num++;
                que.push({ny,nx});
                visit[ny][nx] = true;
            }
        }
    }
    if(num==7) return true;
    else return false;

}
void recur(int x,int cnt,int s){
    if(cnt == 7){
        if(s>=4) {
            if(bfs()){
                result++;
            }
        }
        return;
    }
    for(int i=x;i<25;i++){
        if(sel[i]) continue;
        sel[i] = true;
        if(board[i/5][i%5]=='S') recur(i,cnt+1,s+1);
        else recur(i,cnt+1,s);
        sel[i] = false;
    }
}
int main(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++) cin >> board[i][j];
    }
    recur(0,0,0);
    cout << result;
    return 0;
}