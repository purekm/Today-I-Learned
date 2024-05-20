#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

queue<int> nonbridge;
deque<pair<int,int>> onbridge;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, w, l, time;
    cin >> n >> w >> l;

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        nonbridge.push(k);
    }

    time = 0;  // 초기화
    int total = 0;
    while(true){
        if(nonbridge.empty()&&onbridge.empty()){
            cout << time+1;
            break;
        }else time ++;
        if(!nonbridge.empty()&&total+nonbridge.front()<=l){
            onbridge.push_back({nonbridge.front(),0});
            total += nonbridge.front();
            nonbridge.pop();
        }
        for(int i=0;i<onbridge.size();i++){
            onbridge[i].second++;
        }
        if(onbridge.front().second == w){
            total -= onbridge.front().first;
            onbridge.pop_front();
        }

    }
    return 0;
}