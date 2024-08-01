#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>


using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m;
    cin >> n;
    map<int,int> map;
    set<pair<int,int>> set;
    for(int i=0;i<n;i++){
        int num, level;
        cin >> num >> level;
        set.insert({level,num});
        map[num] = level;
    }
    cin >> m;
    for(int i=0;i<m;i++){
        string instruction;
        cin >> instruction;
        if(instruction == "recommend"){
            int x;
            cin >> x;
            if(x==1) {
                auto it = set.rbegin();
                cout << (*it).second<< '\n';
            }
            if(x==-1) {
                auto it = set.begin();
                cout << (*it).second << '\n';
            }
        }else if(instruction == "add"){
            int l,p;
            cin >> l >> p;
            set.insert({p,l});
            map[l] = p;
        }else if(instruction == "solved"){
            int p;
            cin >> p;
            set.erase({map[p],p});
            map.erase(p);
        }
    }
    
    return 0;
}
