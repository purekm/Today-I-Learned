#include <iostream>
#include <array>
#include <string>
#include <list>


using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    list<char> lt;
    string s; // 입력 문자열
    int n; // 횟수
    cin >> s >> n;

    for(auto e : s) lt.push_back(e);
    auto cursur = lt.end();

    for(int i=0;i<n;i++){
        char op;
        cin >> op;
        switch (op)
        {
            case 'L' :
                if(cursur != lt.begin()) cursur--;
                break;
            case 'D' :
                if(cursur != lt.end()) cursur++;
                break;
            case 'B' :
                if(cursur != lt.begin()) cursur = lt.erase(--cursur);
                break;
            case 'P' :
                char k;
                cin >> k;
                lt.insert(cursur,k);
                break;
        }
    }
    for(auto e : lt) cout << e;

    return 0;
}