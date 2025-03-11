#include <iostream>
#include <array>
#include <vector>
#include <string>


using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> alp(26);
    string s1,s2;
    int ans = 0;
    cin >> s1 >> s2;
    for(char c : s1) alp[c-'a']++;
    for(char c : s2) alp[c-'a']--;

    for(int i=0;i<26;i++){
        if(alp[i]>=0) ans+=alp[i];
        else ans-=alp[i];
    }
    cout << ans;

    return 0;
}
/*서로 다른 문자열에 문자 개수를 세서, 서로 빼면 다른 문자 개수만 남지 않을까?*/
