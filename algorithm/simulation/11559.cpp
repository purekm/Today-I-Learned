#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
char board[12][6];
bool visit[12][6];
int result;
void down(){
    for(int i=10;i>=0;i--){
        for(int j=0;j<6;j++){
            if(board[i][j]!='.'){
                int x = i;
                int y = j;
                while(true){
                    if(x+1<=11){
                        if(board[x+1][y]=='.'){
                            board[x+1][y] = board[x][y];
                            board[x][y] = '.';
                            x+=1;
                        }else break;
                    }else break;
                }
            }
        }
    }
}
bool check(int x,int y){
    queue<pair<int,int>> que;
    queue<pair<int,int>> change;
    que.push({x,y});
    change.push({x,y});
    visit[x][y] = true;
    int cnt = 1;
    while(!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        for(int k=0;k<4;k++){
            int nx = cur.first + dx[k];
            int ny = cur.second + dy[k];
            if(nx<0||nx>=12||ny<0||ny>=6) continue;
            if((board[nx][ny]!=board[x][y])||visit[nx][ny]) continue;
            visit[nx][ny] = true;
            que.push({nx,ny});
            change.push({nx,ny}); //바뀌는 점들을 change에 저장 
            cnt++; 
        }
    }
    if(cnt >= 4){ //cnt>=4 면 change에 있는 점들을 빈칸으로 변경
        while(!change.empty()){
            pair<int,int> now = change.front();
            change.pop();
            int nx = now.first;
            int ny = now.second;
            board[nx][ny] = '.';
        }
        return true;
    }
    memset(visit,0,sizeof(visit));
    return false;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    result = 0;
    for(int i=0;i<12;i++){
        for(int j=0;j<6;j++) cin >> board[i][j];
    }
    while(true){
        bool flag = false;
        for(int i=0;i<12;i++){
            for(int j=0;j<6;j++){
                if(board[i][j] != '.'){
                    if(check(i,j)) flag = true;
                }
            }
        }
        if(!flag) break;
        else{
            result++;
            down();
        }
    }
    cout << result;
    return 0;
}