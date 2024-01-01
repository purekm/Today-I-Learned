#include<iostream>
#include<cmath>

using namespace std;
int k,n,r,c;
int board[20000][20000];
void recur(int n,int x,int y){
    if(n == 1){
        board[x][y]=k;
        board[x][y+1]=k+1;
        board[x+1][y]=k+2;
        board[x+1][y+1]=k+3;
        k += 4;
    }else{
        recur(n-1,x,y);
        recur(n-1,x,y+pow(2,n-1));
        recur(n-1,x+pow(2,n-1),y);
        recur(n-1,x+pow(2,n-1),y+pow(2,n-1));
    }
    return;
}
int main(){
    int k=0;
    cin >> n >> r >> c;
    recur(n,0,0);
    for(int i=0; i<pow(2,n);i++){
        for(int j=0; j<pow(2,n);j++){
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }
    cout << board[r][c];
    return 0;
}