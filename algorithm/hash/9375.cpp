#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int num;
        cin >> num;
        int cnt = 0;
        string type,clothes;
        unordered_map<string,int> s;
        for(int j=0; j<num; j++){
            cin >> clothes >> type;
            s[type]++;
        }
        cnt = 1;
        for(auto a: s){
            cnt *= (a.second+1);
        }
        cnt--;
        cout << cnt << '\n';
    }
    return 0;
}
