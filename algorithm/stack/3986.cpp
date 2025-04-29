#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    int n;
    stack<char> goodword;
    cin >> n;
    for(int i=0; i<n;i++){
        string s;
        cin >> s;
        for(int l=0; l<s.length();l++){
            goodword.push(s[l]);
        }


    }
    return 0;
    }
