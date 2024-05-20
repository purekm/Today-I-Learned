#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;


int main(){
    int n;
    cin >> n;
    int board[100001];
    int dp[100001];
    for(int i=0;i<n;i++){
        cin >> board[i];
        dp[i] = board[i];
    }
    int maxnum = dp[0];
    for(int i=1;i<n;i++){
        dp[i] = max(dp[i],board[i]+dp[i-1]);
        if(dp[i]>maxnum) maxnum = dp[i];
    }
    cout << maxnum;
    return 0;
}