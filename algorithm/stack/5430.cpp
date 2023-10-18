#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    deque<int> que;
    
    for(int i=0;i<t;i++){
        string s = "";
        string arr = "";
        int num=0;
        int dcount = 0;
        int rcount = 0; //D,R의 개수를 세어줌
        string string = "";
        cin >> s >> num >> arr; 
        for (int j = 0; j < arr.length(); j++) {
            if (isdigit(arr[j])) {
                string += arr[j]; // 문자열 's'에 숫자 문자를 추가
            } else {
                if (!string.empty()) {
                    que.push_back(stoi(string)); // 문자열 's'를 정수로 변환하여 que에 추가
                    string.clear(); // 문자열 's' 초기화
                }
            }
        }
        for(char ch:s){
            if(ch == 'R'){
                rcount++;
            }else if(ch == 'D'){
                if(!que.empty()) {
                    if(rcount %2 == 0) que.pop_front();
                    else que.pop_back();
                }
                dcount++;
            }
        }
        if(rcount%2==1){
            reverse(que.begin(),que.end());
        }
        if(dcount>num) cout << "error\n";
        else{
            cout <<'[';
            while(!que.empty()){
                if(que.size()!=1){
                    cout << que.front()<<',';
                    que.pop_front();
                }else{
                    cout << que.front();
                    que.pop_front();
                }
            }
            cout <<']'<<'\n';
        }
    }
    return 0;
}