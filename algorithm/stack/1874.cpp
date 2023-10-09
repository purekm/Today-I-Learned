#include <iostream>
#include <array>
#include <stack>
#include <list>

using namespace std;

int main(){
    int n = 0;
    int num;
    int j=0;
    stack<int> stack;
    list<char> arr={};
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> num;
        while(j<num){
            stack.push(j+1);
            arr.push_back('+');
            j++;
        }
        if(stack.top()==num){
            stack.pop();
            arr.push_back('-');
        }
    }
    if(!stack.empty()){
        cout << "NO";
    }else{
        for (auto i:arr){
            cout<< i <<'\n';
        }
    }
    
    
    return 0;
}