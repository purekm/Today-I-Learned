#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,s;
    cin >> n >> s;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];
    int start = 0;
    int end = 0;
    int sum = 0;
    int length = 100001;
    while(end<=n){
        if(sum<s){
            sum += arr[end];
            end++;
        }else{
            length = min(length,end-start);
            sum -= arr[start];
            start++;
            
        }
    }
    if(length == 100001) cout << 0;
    else cout << length;
    
    return 0;
}
