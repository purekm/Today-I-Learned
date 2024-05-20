#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


int main(){
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        int n,num,k;
        int arr[20]={0,};
        int dp[10001] ={0,};
        k = 0;
        cin >> n;
        for(int j=0;j<n;j++){
            cin >> arr[j];
        }
        cin >> num;
        dp[0] = 1;
        for(int j=0; j<n; j++){
            k = arr[j];
            while(k<=num){
                dp[k] = dp[k] + dp[k-arr[j]];
                k++;
            }
        }

        cout <<  dp[num] << '\n';

    }
    return 0;
}