#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int Max(int a,int b){
    return a>b ? a : b;
}

int main(){
    int t;
    cin >> t;
    int* time = new int[t+1];
    int* pay = new int[t+1];
    int* dp = new int[t+1];
    
    for(int i=0;i<t;i++){
        cin >> time[i] >> pay[i];
    }
    int m = 0;
    for(int i=0;i<=t;i++){
        dp[i] = max(m,dp[i]);
        if(i+time[i]<=t) dp[i+time[i]] = Max(dp[time[i]+i],dp[i]+pay[i]);
        m = Max(m,dp[i]);
    }
    cout << m << '\n';
    return 0;
}