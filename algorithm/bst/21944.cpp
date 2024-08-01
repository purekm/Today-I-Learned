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
    map<int, set<pair<int,int>>> problem;
    map<int,pair<int,int>> maps;
    set<pair<int,int>> s;
    for(int i=0;i<n;i++){
        int num, level,algorithm;
        cin >> num >> level >> algorithm;
        problem[algorithm].insert({level,num}); //알고리즘 신경 쓴 set들
        s.insert({level,num}); //알고리즘 상관 없는 set
        maps[num] = {level,algorithm};
    }
    cin >> m;
    for(int i=0;i<m;i++){
        string instruction;
        cin >> instruction;
        if(instruction == "recommend"){
            int x,g;
            cin >> g >> x;
            if(x==1) cout << problem[g].rbegin()->second << '\n';
            if(x==-1) cout << problem[g].begin()->second << '\n';
        }else if(instruction == "recommend2"){
            int x;
            cin >> x;
            if(x==1) cout << s.rbegin()->second << '\n';
            if(x==-1) cout << s.begin()->second << '\n';
        }else if(instruction == "recommend3"){
            int x , l;
            cin >> x >> l;
            auto it = s.lower_bound({l,0});
            if(x==1){
                if(it == s.end()) cout << -1 << '\n';
                else cout << it->second << '\n';
            }
            if(x==-1){
                if(it == s.begin()) cout << -1 << '\n';
                else cout << (--it)->second << '\n';
            }
        }else if(instruction == "add"){
            int l,p,g;
            cin >> l >> p >> g;
            s.insert({p,l});
            problem[g].insert({p,l});
            maps[l] = {p,g};
        }else{
            int p;
            cin >> p;
            auto [level,algorithm] = maps[p];
            problem[algorithm].erase({level,p});
            s.erase({level,p});
            maps.erase(p);
        }
    }
    return 0;
}
