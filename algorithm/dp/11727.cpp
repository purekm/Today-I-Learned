#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main(){
    int n;
    cin >> n;
    int board[1001];
    board[1] = 1;
    board[2] = 3; 
    for(int i=3;i<=n;i++){
        board[i] = board[i-1]+board[i-2]*2;
        board[i] %= 10007;
    }
    cout << board[n];

    
    return 0;
}