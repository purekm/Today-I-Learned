#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
bool prime[4000001];
vector<int> arr;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    memset(prime, true, sizeof(prime));
    prime[0] = false;
    prime[1] = false;
    for(int i=2;i*i<=n;i++){
        if(prime[i]){
            for(int j=i+i; j<=n; j+=i){
                prime[j] = false;
            }
        }
    }
    for(int i=2;i<=n;i++) {
        if(prime[i]) arr.push_back(i);
    }
    int start = 0;
    int end = 0;
    int sum = 0;
    int cnt = 0;

    while(end <= arr.size()){
        if(sum<n){
            if(end == arr.size()) break;
            sum+=arr[end];
            end++;
        }else{
            if(sum==n) cnt++;
            start++;
            end = start;
            sum = 0;
        }
    }
    cout << cnt;
    
    return 0;
}
