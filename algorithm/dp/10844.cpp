#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;


int main(){
    int t;
    long long dp[101][10];

    cin >> t;
    for(int i=1;i<=9;i++) dp[0][i] = 1;
    dp[0][0] = 0;
    for(int i=1;i<=t;i++){
        dp[i][0] = dp[i-1][1]%1000000000;
        dp[i][1] = (dp[i-1][0]+dp[i-1][2])%1000000000;
        dp[i][2] = (dp[i-1][1]+dp[i-1][3])%1000000000;
        dp[i][3] = (dp[i-1][2]+dp[i-1][4])%1000000000;
        dp[i][4] = (dp[i-1][3]+dp[i-1][5])%1000000000;
        dp[i][5] = (dp[i-1][4]+dp[i-1][6])%1000000000;
        dp[i][6] = (dp[i-1][5]+dp[i-1][7])%1000000000;
        dp[i][7] = (dp[i-1][6]+dp[i-1][8])%1000000000;
        dp[i][8] = (dp[i-1][7]+dp[i-1][9])%1000000000;
        dp[i][9] = dp[i-1][8]%1000000000;
    }
    long long sum = 0;
    for(int i=0;i<10;i++){
        sum += dp[t-1][i];
    }
    sum %= 1000000000;
    cout << sum << '\n';
    return 0;
}