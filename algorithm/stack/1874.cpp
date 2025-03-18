#include <iostream>
#include <array>
#include <stack>
#include <list>

using namespace std;

int main(){
    stack<int> s;
    list<int> lt;
    string result;
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        int num;
        cin >> num;
        lt.push_back(num);
    }
    int idx = 1;
  
    while(!lt.empty() && idx<=n+1){

        if(s.empty()) {
            s.push(idx++);
            result+="+\n";
        }
    
        if(s.top()!=lt.front()){
            s.push(idx++);
            result+="+\n";
        }
        if(s.top() == lt.front()){
            lt.pop_front();
            s.pop();
            result+="-\n";
        }
        
    }
    if(lt.empty()){
        cout << result;
    }else{
        cout << "NO" ;
    }
    return 0;
}
// 굳이 result 리스트를 쓰지않고, string result에 기호를 더해나가는 방식도 좋은 것 같다
// 2중 while문을 회피하기 위해 이렇게 작성했는데, 괜찮은 방식인지 모르겠다.
// 입력을 먼저 받지 말고, 입력과 함께 프로세스를 처리한다면 더 좋은 방식이 되었을 것 같다.
