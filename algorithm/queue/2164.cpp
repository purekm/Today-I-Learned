#include <iostream>
#include <array>
#include <queue>

using namespace std;

int main(){
    queue<int> que;
    int num = 0;
    cin >> num;
    for(int i=1; i<=num;i++){
        que.push(i);
    }
    while(que.size()>1){
        que.pop();
        que.push(que.front());
        que.pop();
    }

    cout<< que.front();
    return 0;
}