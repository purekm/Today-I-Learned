#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;
unordered_map<string,int> s;
bool compare(pair<string,int> &first,pair<string,int> &second){
    return first.second < second.second;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k,l;
    cin >> k >> l;
    vector<pair<string,int>> vec;
    for(int i=0;i<l;i++){
        string num;
        cin >> num;
        s[num] = i;
    }
    for(auto e : s) vec.push_back(e);
    sort(vec.begin(),vec.end(),compare);
    int cnt = min(k,(int)vec.size());
    for(int i=0;i<cnt;i++){
        cout << vec[i].first << " ";
    }
    return 0;
}
