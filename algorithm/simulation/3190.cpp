#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,k,l,length = 1;
    cin >> n >> k;
    int board[101][101];
    int visit[101][101];
    for(int i=0;i<n;i++){
        fill(board[0],board[n],0);
        fill(visit[0],visit[n],0);
    }
    queue<pair<int,char>> direction;
    queue<pair<int,int>> snake;
    for(int i=0;i<k;i++){
        int row,col;
        cin >> row >> col;
        board[row-1][col-1] = 1;
    }
    cin >> l;
    for(int i=0;i<l;i++){
        int x;
        char cha;
        cin >> x >> cha;
        direction.push({x,cha});
    }
    int time = 0;
    int r = 0;
    int c = 0;
    int d = 0;
    
    snake.push({r,c}); // 뱀이 있는 위치를 쌓음
    visit[r][c] = 1;
    while(true){
        time++;
        auto cur = snake.back(); // 머리 
        int nr = cur.first + dr[d];
        int nc = cur.second + dc[d];
        
        if(nr>=n||nr<0||nc>=n||nc<0 || visit[nr][nc]) {
            break;
        }
        if(board[nr][nc] == 1){
            board[nr][nc] = 0;
            snake.push({nr,nc});
            length++;
            visit[nr][nc]++;
        }else{
            auto tail = snake.front(); // 꼬리
            visit[tail.first][tail.second] = false;
            snake.push({nr,nc});
            visit[nr][nc] ++;
            snake.pop();
        }
        if(time == direction.front().first){
            char direct = direction.front().second;
            if(direct == 'L') d = (d+3)%4;
            else d = (d+1)%4;
            direction.pop();
        }
    }
    cout << time;
    
    return 0;
}