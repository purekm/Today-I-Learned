#include <iostream>
#include <array>
#include <stack>
#include <string>


using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    stack<int> stack;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        string s;
        cin >> s;
        
        if(s=="push"){
            int num;
            cin >> num;
            stack.push(num);
        }
        else if(s=="pop"){
            if(stack.empty()) cout << -1 << '\n';
            else {
                cout << stack.top() <<'\n';
                stack.pop();
            }
        }
        else if(s=="size"){
            cout << stack.size() <<'\n';
        }
        else if(s=="empty"){
            if(stack.empty()) cout << 1 << '\n';
            else cout << 0 << '\n';
        }
        else if(s=="top"){
            if(stack.empty()) cout << -1 << '\n';
            else cout << stack.top() <<'\n';
        }
        
    }
    
    return 0;
}

