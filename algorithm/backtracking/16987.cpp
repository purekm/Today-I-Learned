#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>

using namespace std;
int n;
int result = 0;
pair<int,int> arr[9];
bool broke[9];
bool visit[9];
int big;

void recur(int k){
    bool hit = false;
    if(k==n){
        for(int i=0;i<n;i++){
            if(arr[i].first<=0) result++;
        }
        if(big < result) big = result;
        result = 0;
        return;
    }
    for(int i=0;i<n;i++){
        if(arr[i].first <= 0 || arr[k].first <= 0) continue;
        if(i==k)continue;
        arr[k].first -= arr[i].second;
        arr[i].first -= arr[k].second;
        hit = true;
        recur(k+1);
        arr[k].first += arr[i].second;
        arr[i].first += arr[k].second;
    }
    if(!hit) recur(k+1);
}
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i].first;
        cin >> arr[i].second;
    }
    recur(0);
    cout << big;
    return 0;
}