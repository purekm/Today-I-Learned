#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;


int vec_idx[1000000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> vec(n);
    vector<int> vec2(n);
    vector<int> result;
    vector<int> index(n);
    for(int i=0;i<n;i++){
        cin >> vec[i];
        vec2[i] = vec[i];
    }
    sort(vec2.begin(),vec2.end());
    vec2.erase(unique(vec2.begin(),vec2.end()),vec2.end());
    int length = 0;
    for(int i=0;i<n;i++){
        index[i] = lower_bound(vec2.begin(),vec2.end(),vec[i])-vec2.begin();
        length = max(length,index[i]);
    }
    

    result.push_back(vec[0]);
    
    for(int i=1;i<n;i++){
        if(vec[i]>result.back()){
            result.push_back(vec[i]);
        } 
        else{
            auto idx = lower_bound(result.begin(),result.end(),vec[i])-(result.begin());
            result[idx] = vec[i];
        }
    }
    set<int> sets;
    int find_index = result.size()-1;
    for(int i=n-1;i>=0;i--){
        if(index[i] == find_index){
            find_index--;
            sets.insert(vec[i]);
        }
    }
    
    cout << result.size() << '\n';
    for(auto e : sets) cout << e << " ";
    return 0;
}