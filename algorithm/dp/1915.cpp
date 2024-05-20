#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


int main(){
    int n,m;
    cin >> n >> m;
    int arr[1001][1001];
    int dp[1001][1001];
    for(int i=0;i<n;i++){
        string s = " ";
        cin >> s;
        for(int j=0;j<m;j++){
            arr[i][j] = s.at(j);
            dp[i][j] = arr[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(dp[i][j]==1){

            } 
        }
    }

    
    return 0;
}