#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int arr[100001];
int main(){
    int n,sum,weight;
    weight = 0;
    sum = 0;

    cin >> n;
    for(int i=1;i<=n;i++) cin >> arr[i];
    sort(arr+1,arr+n+1,greater<int>());
    for(int i=1;i<=n;i++){
        sum = arr[i]*i;
        if(sum < weight) continue;
        weight = sum ;

    }
    cout << weight;
    return 0;
}