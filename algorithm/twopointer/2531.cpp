#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int arr[30001];
int visit[3001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,d,k,c;
    cin >> n >> d >> k >> c;
    for(int i=0;i<n;i++) cin >> arr[i];
    int end = 0;
    int result = 0;
    int sum = 0;
    int cnt = 0;
    for(int i=0;i<n;i++){
        while(cnt<k){
            if(!visit[arr[end%n]]) {
                sum++;
            }
            visit[arr[end%n]]++;
            end++;
            cnt++;
        }
        if(visit[c]==0) result = max(result,sum+1);
        else result = max(result,sum);

        visit[arr[i]]--;
        cnt--;
        if(visit[arr[i]]==0) sum--;
    }
    cout << result;
    return 0;
}
