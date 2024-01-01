#include<iostream>

using namespace std;
int n,m;
int arr[10];
bool visit[10];
void recur(int k,int start){
    if(k==m){
        for(int i=0;i<m;i++){
            cout << arr[i] << " ";
        }
        cout << '\n';
        return;
    }
    for(int i=start;i<=n;i++){
        if(!visit[i]){
            arr[k] = i;
            visit[i] = true;
            recur(k+1,i+1);
            visit[i] = false;
        }
    }


}
int main(){
    cin >> n >> m;
    recur(0,1);
    return 0;
}