#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;


int main(){
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        long long board[101];
        board[1] = 1;
        board[2] = 1;
        board[3] = 1;
        board[4] = 2;
        board[5] = 2;
        int num;
        cin >> num;
        for(int j=6;j<=num;j++){
            board[j] = board[j-1]+board[j-5];
        }
        cout << board[num] << '\n';
    }
    return 0;
}