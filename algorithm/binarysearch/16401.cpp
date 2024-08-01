#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
vector<int> snack;


int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int m,n,num;
    cin >> m >> n;
    for(int i=0;i<n;i++){
        cin >> num;
        snack.push_back(num);
    }
    sort(snack.begin(),snack.end());
    int low = 1; 
    int high = snack[n-1];
    int result = 0;
    while(low<=high){
        int mid = (low+high)/2;
        int cnt = 0;
        for(int i=0;i<n;i++){
            cnt += snack[i]/mid;
        }
        if(cnt >= m) {
            result = mid;
            low = mid+1;
        }else 
            high = mid-1;
    }
    cout << result;
    return 0;
}