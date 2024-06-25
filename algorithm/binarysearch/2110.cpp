#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int arr[200001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,c,width;
    cin >> n >> c;
    for(int i=0;i<n;i++) cin >> arr[i];
    sort(arr,arr+n);

    int start = 1;
    int end = arr[n-1] - arr[0];
    int result = 0;
    while(end>=start){
        int mid = (start+end)/2;
        int last = arr[0];
        int cnt = 1;
        for(int i=0;i<n;i++){
            if(arr[i]-last >= mid){
                cnt++;
                last = arr[i];
            }
        }
        if(cnt >= c){
            result = mid;
            start = mid + 1;
        }else  
            end = mid - 1;
    }
    cout << result;
    return 0;
}