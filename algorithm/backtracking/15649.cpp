#include<iostream>

using namespace std;
int n,m;
int arr[10];
bool visit[10];
void recur(int k){
    if(k==m){
        for(int i=0;i<m;i++){
            cout << arr[i] << ' ';
        }
        cout <<'\n';
        return;
    }
    for(int i=1;i<=n;i++){
        if(visit[i]) continue;
        visit[i] = true;
        arr[k] = i;
        recur(k+1);
        visit[i] = false;
    }
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    recur(0);
    return 0;
}