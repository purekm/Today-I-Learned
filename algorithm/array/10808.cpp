#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> vec(26);
    string s;
    cin >> s;
    for(char c : s){
        vec[c-'a']++;
    }
    for(int i=0; i<26;i++){
        cout << vec[i] << " ";
    }
    return 0;
}