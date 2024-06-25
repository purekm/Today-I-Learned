#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int arr[100001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    int zero = 0;
    int minimum = 2000000000;
    int result1,result2;
    for(int i=0; i<n;i++) {
        cin >> arr[i];
        if(arr[i]>0 && !zero) zero = i;
    }
    if(!zero){ // 모두 양수거나 모두 음수인 경우 예외처리
        if(arr[0]>0){
            cout << arr[0] << " " << arr[1];
            return 0;
        }else{
            cout << arr[n-2] << " " << arr[n-1];
            return 0;
        }
    }
    
    for(int i=0;i<n-1;i++){
        int start = i+1;
        int end = n-1;
        while(start<=end){
            int mid = (start+end)/2;
            int sum = arr[i]+arr[mid];

            if(abs(sum)<abs(minimum)){
                minimum = sum;
                result1= i;
                result2 = mid;
            }
            if(sum<0) start = mid+1;
            else end = mid-1;
        }
    }
    cout << arr[result1] << " "<< arr[result2];
    return 0;
}