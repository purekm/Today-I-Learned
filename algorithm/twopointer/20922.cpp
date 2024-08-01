#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int arr[200001];
int visit[100001]={0,};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    int start = 0;
    int end = 0;
    int cnt = 0;
    int result = 0;
    for(int i=0; i<n; i++){
        while(end<n){
            if(visit[arr[end]]<k){
                visit[arr[end]]++;
                end++;
            }else{
                break;
            }
        }
        result = max(result,end - i);
        visit[arr[i]]--;
    }
    cout << result;
    return 0;
}
