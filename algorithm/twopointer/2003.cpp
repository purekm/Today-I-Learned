#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int arr[10001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> arr[i];
    
    int start = 0;
    int end = 0;
    int sum = 0;
    int cnt = 0;
    while(end<=n){
        if(sum<m){
            sum += arr[end];
            end++;
        }else{
            if(sum == m) cnt++;
            sum = 0;
            start++;
            end = start;
        }
    }
    cout << cnt;
    
    return 0;
}
