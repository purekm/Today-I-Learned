#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>

using namespace std;
set<pair<int,int>> information;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int,int>> arr(n);
    multiset <int> ms;
    for(int i=0;i<n;i++){
        int h , k;
        cin >> h >> k;
        arr[i] = {h,k};
    }
    sort(arr.begin(),arr.end(),greater<>());

    for(int i=0;i<n;i++){
        auto iter = ms.upper_bound(arr[i].second-1);
        if(ms.empty()) {
            ms.insert(1);
            continue;
        }
        if(iter == ms.begin()){
            ms.insert(1);
        }else{
            iter--;
            ms.erase(iter);
            ms.insert((*iter)+1);
        }
    }
    cout << ms.size();
    return 0;
}