#include <iostream>
#include <array>
#include <stack>

using namespace std;

int main(){
    int n;
    int sum = 0;
    stack<int> s;
    cin >> n;
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        if (num) s.push(num);
        else s.pop();
    }
    while(!s.empty()){
        sum += s.top();
        s.pop();
    }
    cout << sum;
    return 0;
}