#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int arr[100001];
bool visit[100001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    for(int i=0;i<n;i++) cin >> arr[i];

    long long cnt = 0;
    int end = 0;
    for(int i=0;i<n;i++){
        while(end < n){
            if(!visit[arr[end]]) {
                visit[arr[end]] = true;
                end++;
            }else{
                break;
            }
        }
        cnt +=(end-i);
        visit[arr[i]] = false;
    }
    cout << cnt;
    
    return 0;
}
