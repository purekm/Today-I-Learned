#include <iostream>
#include <array>
#include <deque>
#include <list>

using namespace std;

int main(){
    deque<int> que;
    int n,m,num;
    int cnt = 0; // 횟수
    cin >>n;
    cin >>m;
    for(int i=1;i<=n;i++){
        que.push_back(i);
    }
    for(int i=1;i<=m;i++){
        cin >> num;
        int left = 0;
        int right = 0;
        for(int j=0; j<que.size();j++){
            if(que[j] == num){
                left = j;
                right = que.size()-j;
            }
        }
        if(left > right){
            while(que.front() != num){
                que.push_front(que.back());
                que.pop_back();
                cnt++;
            }
            que.pop_front();
        }else{
            while(que.front()!=num){
                que.push_back(que.front());
                que.pop_front();
                cnt++;
            }
            que.pop_front();
        }
    }
    cout << cnt;
    return 0;
}