#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
vector<pair<int,int>> vec;

int main(){
   cin.tie(nullptr);
   ios::sync_with_stdio(false);
   int n;
   int sum = 0;
   cin >> n;
   for(int i=0;i<n;i++){
    int a,b;
    cin >> a >> b;
    vec.push_back({a,b});
   }
   sort(vec.begin(),vec.end());
   int start = vec[0].first;
   int finish = vec[0].second;
   for(int i=1;i<n;i++){
    if(vec[i].first<=finish && vec[i].second>=finish){
        finish = vec[i].second;
    }else if(vec[i].first > finish){
        sum += finish-start;
        start = vec[i].first;
        finish = vec[i].second;
    }else continue;
   }
    sum += finish-start;
    cout << sum;
    return 0;
}