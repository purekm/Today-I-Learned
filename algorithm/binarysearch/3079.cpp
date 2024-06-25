#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long long arr[100001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> arr[i];
    sort(arr,arr+n);

    long long result = 0;
    long long start = 0;
    long long end = arr[0]*m;
    while(start<=end){
        long long mid = (start+end)/2;
        long long cnt = 0;
        for(int i=0;i<n;i++) {
            cnt += mid/arr[i];
        }
        if(cnt >= m) {
            result = mid;
            end = mid - 1;
        }
        else 
            start = mid + 1;
    }
    cout << result;
    return 0;
}
