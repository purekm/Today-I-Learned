#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <set>
using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<int,multiset<int>> maps;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int dead,cup;
        cin >> dead >> cup;
        maps[dead].insert(cup);
    }
    priority_queue<int> pq;
    int sum = 0;
    for(int i=n;i>0;i--){
        for(auto e : maps[i]) pq.push(e);
        if (!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
    }
    cout << sum;
    
    return 0;
}
