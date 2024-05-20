#include<iostream>
#include<algorithm>

using namespace std;
int n,cnt;
bool visit1[22];
bool visit2[22];
bool visit3[22];

void backtracking(int k){
    if(k==n) {
        cnt++;
        return;
    }
    for(int i=0;i<n;i++){
        if(visit1[i]||visit2[i+k]||visit3[k-i+n-1]) continue;
        visit1[i] = true;
        visit2[i+k] = true;
        visit3[k-i+n-1] = true;
        backtracking(k+1);
        visit1[i] = false;
        visit2[i+k] = false;
        visit3[k-i+n-1] = false;
    }
}
int main(){
    cnt = 0;
    cin >> n;
    backtracking(0);
    cout << cnt;
    return 0;
}