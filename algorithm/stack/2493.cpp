#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n=0;
    int high = 0;
    cin >> n;
    int height;
    stack<pair<int,int>> s; //pair을 써서 인덱스랑 height를 함께 쓰자
    for(int i=0; i<n;i++){
        cin >> height;
        while(!s.empty()){
            if(height<s.top().second){
                cout << s.top().first << ' ';
                break;
            }
            s.pop();
        }
        if(s.empty()) cout << 0 <<' ';
        s.push(make_pair(i+1,height)); // make_pair을 통해 pair생성 가능
    }
    return 0;
}

//스택에 필요한 정보들을 넣고, top과 비교하는 값을 비교해야 할때 stack사용