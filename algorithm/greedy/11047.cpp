#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main(){
    int n,k,sum,cnt,num;
    cin >> n >> k;
    sum = 0;
    cnt = 0;
    num = 0;
    int coin[11];
    for(int i=0;i<n;i++){
        cin >> coin[i];
    }
    sort(coin,coin+n,greater<int>());
    while(sum<k){
        if(sum+coin[num]>k){
            num++;
        }else{
            sum += coin[num];
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}