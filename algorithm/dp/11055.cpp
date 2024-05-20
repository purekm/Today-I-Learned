#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;


int main(){
    int n,m;
    cin >> n;
    int board[1001];
    int dp[1001];
    m = 0;
    for(int i=0;i<n;i++){
        cin >> board[i];
        dp[i] = board[i];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(board[i]<=board[j] || dp[i]>=dp[j]+board[i]) continue;
            dp[i]=dp[j]+board[i];
        }
        cout << dp[i] << '\n';
        if (m<dp[i]) m =dp[i];
    }
    cout << m;
    return 0;
}