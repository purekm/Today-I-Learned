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
    vector<int> result;
    
    for(int i=0;i<n;i++){
        cin >> vec[i];
    }
    result.push_back(vec[0]);
    vec_idx[0] = 0;
    for(int i=1;i<n;i++){
        if(vec[i]>result.back()){
            result.push_back(vec[i]);
            vec_idx[i] = result.size()-1;
        } 
        else{
            auto idx = lower_bound(result.begin(),result.end(),vec[i])-(result.begin());
            result[idx] = vec[i];
            vec_idx[i] = idx;
        }
    }
    set<int> sets;
    int find_index = result.size()-1;
    for(int i=0;i<n;i++) cout << vec_idx[i] << " ";
    for(int i=n-1;i>=0;i--){
        if(vec_idx[i] == find_index){
            find_index--;
            sets.insert(vec[i]);
        }
    }
    
    cout << result.size() << '\n';
    for(auto e : sets) cout << e << " ";
    return 0;
}