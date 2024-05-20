#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

long long arr[40];

long long fib(int num){
    if(num==0||num==1){
        arr[num] = num;
    }else if(arr[num]==0){
        arr[num] = fib(num-1)+fib(num-2);
    }
    return arr[num];
}
int main(){
    int t,n;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n;
        if(n == 0) cout << 1 << ' ' << 0 << '\n';
        else cout << fib(n-1) << ' ' << fib(n) << '\n';
    }
    return 0;
}