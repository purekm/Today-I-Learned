#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    int n =0;
    int cnt = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        stack<int> stack;
        string s = "";
        cin >> s;
        int k =0;
        while(k<s.length()){
            char c = s.at(k);
            if(!stack.empty()){
                if(stack.top()==c) {
                stack.pop();
                }
                else{
                    stack.push(c);
                }
            }else{
                stack.push(c);
            }
            k++;
        }
        if(stack.empty()) cnt++;
    }
    cout << cnt;
    return 0;
    }
