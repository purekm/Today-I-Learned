#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int arr[1000001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    for(int i=0; i<n; i++) cin >> arr[i];
    int end = 0;
    int result = 0;
    int cnt = 0;
    for(int i=0; i<n; i++){
        while(end<n){
            if(cnt+arr[end]%2>k) break;
            if(arr[end]%2 != 0) cnt++;
            end++;
        }
        result = max(result,end-i-cnt);
        if(arr[i]%2 != 0) cnt--;
    }
    cout << result;
    return 0;
}
