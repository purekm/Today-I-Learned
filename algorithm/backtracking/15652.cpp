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
        arr[k] = i;
        recur(k+1,i);
    }


}
int main(){
    cin >> n >> m;
    recur(0,1);
    return 0;
}