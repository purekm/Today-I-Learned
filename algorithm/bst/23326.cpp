#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>


using namespace std;

set<int> s;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m,pos = 0;
    cin >> n >> m;
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        if(num) s.insert(i);
    }
    for(int i=0; i<m; i++){
        int instruction;
        cin >> instruction;
        if(instruction == 1){
            int num;
            cin >> num;
            if(s.count(num-1)) s.erase(num-1);
            else s.insert(num-1);
        }else if(instruction == 2){
            int num;
            cin >> num;
            pos = (pos + num)%n;
        }else{
            if(s.empty()){
                cout << -1 << '\n';
                continue;
            }
            int dis;
            auto it = s.lower_bound(pos);
            if(it != s.end()) dis = *it - pos;
            else{
                int temp = n-pos;
                dis = *s.begin() + temp;
            }
            cout << dis << '\n';
        }
    }
    
    return 0;
}
