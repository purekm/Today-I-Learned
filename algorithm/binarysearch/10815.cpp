#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
int arr[500001];
int arr2[500001];
int result[500001];

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n;
    for(int i=0;i<n;i++) cin >> arr[i];
    cin >> m;
    for(int i=0;i<m;i++) cin >> arr2[i];
    sort(arr,arr+n);
    for(int i=0;i<m;i++){
        int start = 0;
        int end = n-1;
        while(end>=start){
            int mid = (start+end)/2;
            if(arr[mid] == arr2[i]) {
                result[i] = 1;
                break;
            }
            else if(arr2[i]>=arr[mid]){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
    }
    for(int i=0;i<m;i++) cout << result[i] << " ";
    return 0;
}