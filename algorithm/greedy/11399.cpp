#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int arr[1001];
int main(){
    int n;
    int sum = 0;
    int result = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    sort(arr,arr+n);
    for(int i=0;i<n;i++){
        sum = sum + arr[i];
        result += sum;
    }
    cout << result;

    return 0;
}