#include<iostream>

using namespace std;
int n;
char board[5000][10000];
void recur(int k,int x,int y){
    if(k==3){
        board[x-2][y+2] = '*';
        board[x-1][y+1] =  '*';
        board[x-1][y+3] =  '*';
        board[x][y] =  '*';
        board[x][y+1] =  '*';
        board[x][y+2] =  '*';
        board[x][y+3] =  '*';
        board[x][y+4] =  '*';
        return;
    }
    int size = k/2;
    recur(size,x,y);
    recur(size,x,y+2*size);
    recur(size,x-size,y+size);
    
}
int main(){
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<2*n;j++){
            board[i][j] = ' ';
        }
    }
    recur(n,n-1,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<2*n-1;j++){
            cout << board[i][j];
        }
        cout << '\n';
    }
    return 0;
}