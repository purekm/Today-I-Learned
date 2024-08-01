#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    priority_queue<int, vector<int>, greater<int>> pq;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x>0) pq.push(x);
        else {
            if(pq.empty()) cout << 0 << '\n';
            else {
                cout << pq.top() << '\n';
                pq.pop();
            }
        }
    }
    
    
    return 0;
}
