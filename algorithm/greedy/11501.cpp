#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int arr[1000001];
int main(){
    int n;
    cin >> n;
    for(int k=0;k<n;k++){
        int num;
        long long sum = 0;
        cin >> num;
        fill_n(arr,num,0);
        for(int i=0;i<num;i++) cin >> arr[i];

        int maxnum = arr[num-1];
        for(int i=num-1;i>=0;i--){
            if(arr[i] >= maxnum) maxnum=arr[i];
            else sum += maxnum-arr[i];
        }
        cout << sum << '\n';
    } 
    return 0;
}