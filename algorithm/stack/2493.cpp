#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    stack<pair<int,int>> s;

    for(int i=1; i<=n; i++){
        int height;
        cin >> height;

        while(!s.empty()){
            if(s.top().second<=height) s.pop();
            else{
                cout << s.top().first << " ";
                break;
            }
        }
        if(s.empty()) cout << 0 << " ";
        s.push({i,height});
    }
    
    return 0;
}
// stack은 값을 넣으면서 비교를 해보자. 더 쉬워진다


