#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
map<int,int> order;
map<int,int> arr;

bool compare(pair<int, int> a, pair<int, int> b){
    if(a.second == b.second) return order[a.first]<order[b.first];
    else return a.second>b.second;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,c;
    cin >> n >> c;
    for(int i=0;i<n;i++){
        int s;
        cin >> s;
        arr[s]++;
        if(!order[s]) order[s] = i+1; //입력된 순서대로
    }
    vector<pair<int,int>> vec(arr.begin(),arr.end());
    sort(vec.begin(),vec.end(),compare);

    for(int i=0; i<vec.size();i++){
        for(int j=0;j<vec[i].second;j++){
            cout << vec[i].first << " ";
        }
        cout << '\n';
    }
    for(int i=0;i<n;i++){
        cout << order[i] << ' ';
    }
    return 0;
}