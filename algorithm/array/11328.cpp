#include <iostream>
#include <array>
#include <vector>
#include <string>


using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        vector<int> alp(26);
        bool posibility = true;
        string s1,s2;
        cin >> s1 >> s2;
        for(char c : s1) alp[c-'a']++;
        for(char c : s2) alp[c-'a']--;

        for(int i=0;i<26;i++){
            if(alp[i]!=0) {
                posibility = false;
                break;
            }
        }
        if(posibility) cout << "Possible" << '\n';
        else cout << "Impossible" << '\n';
    }
    return 0;
}
/*문자열을 재배열해서 같은 문자열을 만들어낼 수 있는가?
문자의 개수만 같은지 확인하면 되지않을까?
첫번째 문자열을을 셀 땐 더하고, 두번째 문자열을 셀땐 빼는 방식*/
