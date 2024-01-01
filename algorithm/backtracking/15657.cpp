#include<iostream>
#include<algorithm>

using namespace std;
int n,m;
int arr[10];
int result[10];
bool visit[10];
void recur(int k,int start){
    if(k==m){
        for(int i=0;i<m;i++){
            cout << result[i] << " ";
        }
        cout << '\n';
        return;
    }
    for(int i=start;i<=n;i++){
        result[k] = arr[i-1];
        recur(k+1,i);
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> arr[i];
    sort(arr,arr+n);
    recur(0,1);
    return 0;
}