#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    int k = 0;
    int sum = 0;
    stack<int> stack;
    cin >> k;
    for(int i=0; i<k;i++){
        int num = -1;
        cin >>num;
        if(num != 0){
            stack.push(num);
        }else{
            stack.pop();
        }
    }
    while(!stack.empty()){
        sum = sum+stack.top();
        stack.pop();
    }
    cout << sum;
    return 0;
}