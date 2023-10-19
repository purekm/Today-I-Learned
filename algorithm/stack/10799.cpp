#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    int cnt = 0;
    int k =0;
    stack<int> stack;
    string s = "";
    char prev = ' ';
    cin >>s;
    while(k<s.length()){
        char c = s.at(k);
        if(c == ')'){
            stack.pop(); 
            if(prev=='('){
                cnt -=1;
                cnt = cnt+stack.size();
            }
            prev = ')';
        }else{
            stack.push(c);
            cnt++;
            prev ='(';
            }
        k++;
    }
    cout << cnt;
    return 0;
}