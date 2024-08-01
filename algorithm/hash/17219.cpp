#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;
unordered_map<string,string> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        string address,password;
        cin >> address >> password;
        s[address] = password;
    }
    for(int i=0;i<m;i++){
        string address;
        cin >> address;
        if(s.find(address) != s.end()){
            cout << s[address] << '\n';
        }
    }
    return 0;
}
