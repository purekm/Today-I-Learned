#include<iostream>
#include<algorithm>

using namespace std;
int n,m;
int arr[10];
int result[10];
bool visit[10];
void recur(int k){
    if(k==m){
        for(int i=0;i<m;i++){
            cout << result[i] << " ";
        }
        cout << '\n';
        return;
    }
    for(int i=1;i<=n;i++){
        if(result[k] == arr[i-1]) continue;
        result[k] = arr[i-1];     
        recur(k+1);
    }
    result[k] = 0;
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }
    sort(arr,arr+n);
    recur(0);
    return 0;
}