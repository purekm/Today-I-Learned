#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    stack<char> stack;
    string s = "";
    cin >> s;
    int num =1;
    int cnt = 0;
    char prev = ' ';
    for(char c:s){
        if(c=='('){
            stack.push(c);
            num = num *2;
        }else if(c=='['){
            stack.push(c);
            num = num *3;
        }else if(c==')'){
            if(stack.empty()||stack.top() != '(') {
                cnt =0;
                break;
            }
            if(prev=='(') cnt = cnt+num;
            stack.pop();
            num /= 2;
        }else if(c==']'){
            if(stack.empty()||stack.top() != '['){
                cnt =0;
                break;
            } 
            if(prev=='[') cnt = cnt+num;
            stack.pop();
            num /=3;
        }
        prev = c;
    }
    if(stack.empty()){
        cout << cnt;
    }else cout << 0;
    
    return 0;
}