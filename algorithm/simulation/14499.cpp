#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
int n,m,x,y,l,r,top,bottom,front,back,nx,ny;
int board[20][20];

int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};

void roll(int num){
    if(num == 1){
        int temp = top;
        top = l;
        l = bottom;
        bottom = r;
        r = temp;
    }else if(num == 2){
        int temp = top;
        top = r;
        r = bottom;
        bottom = l;
        l = temp;   
    }else if(num == 4){
        int temp = top;
        top = front;
        front = bottom;
        bottom = back;
        back = temp;
    }else if(num == 3){
        int temp = top;
        top = back;
        back = bottom;
        bottom = front;
        front = temp;
    }
}
bool topside(int x_pos,int y_pos,int num){
    nx = x_pos + dx[num-1];
    ny = y_pos + dy[num-1];
    if(nx<0||nx>=n||ny<0||ny>=m) return false;
    roll(num);
    if(board[nx][ny]==0){
        board[nx][ny] = bottom;
    }else{
        bottom = board[nx][ny];
        board[nx][ny] = 0;
    }
    return true;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int x,y,t;
    x = 0; y = 0;
    top = 0; front = 0; r = 0; l = 0; back = 0; bottom = 0;
    cin >> n >> m >> x >> y >> t;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin >> board[i][j];
    }
    for(int i=0;i<t;i++){
        int num;
        cin >> num;
        if(topside(x,y,num)){
            x = nx;
            y = ny;
            cout << top << '\n';
        }
    }
    return 0;
}