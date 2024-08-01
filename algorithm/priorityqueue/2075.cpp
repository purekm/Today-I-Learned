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
        int num;
        cin >> num;
        pq.push(num);
        while(pq.size()>n) pq.pop();
    }
    cout << pq.top();
    
    
    return 0;
}
