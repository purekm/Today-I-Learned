#include<iostream>
#include<algorithm>

using namespace std;
int n;
int arr[14];
int result[14];
bool visit[14];
void recur(int k,int start){
    if(k==6){
        for(int i=0;i<6;i++){
            cout << result[i] << " ";
        }
        cout << '\n';
        return;
    }
    for(int i=start;i<=n;i++){
        if(!visit[i]){
            visit[i] = true;
            result[k] = arr[i-1];     
            recur(k+1,i);
            visit[i] = false;
        }
        
    }
    result[k] = 0;
}
int main(){
    n = 1;
    while(n != 0){
        cin >> n;
        for(int i=0;i<n;i++) {
            cin >> arr[i];
        }
        sort(arr,arr+n);
        recur(0,1);
        cout << '\n';
    }
    return 0;
}