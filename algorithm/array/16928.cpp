#include <iostream>
#include <array>
#include <queue>

using namespace std;

int main(){
    int l,s;
    cin >> l>> s;
    
    int ladder[101] = {0,}; // ladder과 snake 둘다 포함하는 array
    int cnt[101]; // 주사위 횟수;
    bool board[101]; // 방문한 적 있는지 true false
    for(int i=0;i<l+s;i++){ //ladder,snake 시작점과 도착점 설정
        int x,y;
        cin >> x>> y;
        ladder[x]=y;
    }

    queue<int> que; 
    que.push(1);
    cnt[1] = 0; //출발점
    board[1] = true;
    int p = 1;
    while(!que.empty()){
        p = que.front(); //현재 위치
        if(p>=100){
            cout << cnt[p];
        }
        que.pop();
        for(int i=1; i<7;i++){ // 주사위 1~6
            if(p+i <=100){
                if(ladder[p+i] != 0 && !board[ladder[p+i]]){ //사다리나 뱀이 있는 위치이면
                    board[ladder[p+i]]=true; //도착지 방문 true
                    que.push(ladder[p+i]); //도착지가 현재위치가 되므로 push
                    cnt[ladder[p+i]] = cnt[p]+1; //도착지의 주사위 횟수 
                }else if(ladder[p+i] ==0 && !board[p+i]){
                    board[p+i]= true;
                    que.push(p+i);
                    cnt[p+i] = cnt[p]+1;
                }
            }
        }

    }
    return 0;
    
}