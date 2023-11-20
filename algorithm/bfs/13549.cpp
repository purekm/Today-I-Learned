#include <iostream>
#include <array>
#include <queue>
#include <string.h>

using namespace std;

int board[100001] ={0,};
bool visit[1000001];
queue<int> que; //순간이동 큐
queue<int> que2; //+1 or -1 큐
int n,k;
int dx[3] = {2,-1,1};
void bfs(int i){ 
    que.push(i);
    visit[i] = true;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        if(cur==k) return;
        for(int k =0;k<3;k++){ // cur의 상하좌우 탐색
            int nx;
            if(k==0) nx = cur*2;
            else nx = cur+dx[k];
            if(visit[nx]||nx<0||nx>100000) continue;
            visit[nx]= true;
            if(k==0) { //순간이동하는 경우
                board[nx] = board[cur];
                que.push(nx);
            }
            else {
                que2.push(nx);
                board[nx] = board[cur]+1;
            }
            // cout << nx << '\n';
        }
        if(que.empty()){
            que = que2;
            que2 = queue<int>();
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    bfs(n);
    cout << board[k];
    return 0;
}