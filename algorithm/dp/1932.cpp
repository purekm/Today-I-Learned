#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main(){
    int n;
    cin >> n;
    int board[505][505];
    int maxnum = 0;

    for(int i=0; i<n;i++){
        for(int j=0;j<i+1;j++){
            cin >> board[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            if(j == 0) board[i][j] = board[i-1][0] + board[i][j];
            else if(i == j) board[i][j] = board[i-1][j-1]+board[i][j];
            else board[i][j] = max(board[i-1][j-1]+board[i][j],board[i-1][j]+board[i][j]);
        }
    }
    int max = board[0][0];
    for(int i=0;i<n;i++){
        if(board[n-1][i]>max) max = board[n-1][i];
    }
    cout << max;
    return 0;
}