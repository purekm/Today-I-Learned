#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int main(){
    string s;
    int sum = 0;
    cin >> s;
    string k = " ";
    for(int i=0;i<s.length()+1;i++){
        if(s[i]=='+' || s[i]=='-' || i==s.length()){
            int num = stoi(k);
            if(s[i]=='+') sum += num;
            else if(s[i]=='-') sum-= num;
            k = "";
        }else{
            k += s[i];
        }
        cout << sum << " "; 
    }
    return 0;
}