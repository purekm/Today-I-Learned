#include <iostream>
#include <array>
#include <queue>
#include <stack>
#include <string.h>
#include <algorithm>

using namespace std;

int n,k,num; //m,n은 세로와 가로를 나타내고, k는 block 개수, num은 0들의 집합 개수 이다.
int board[100001];
int visit[100001];
int dist[100001];
int pre[100001];
int ans;
queue<int> que;

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> n >> k;
    que.push(n);
    visit[n] = true;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        int dx[3] = {1,-1,cur}; 
        for(int i=0;i<3;i++){
            int nx = cur + dx[i];
            if(nx>=100001||nx<0) continue;
            if(visit[nx]) continue;
            visit[nx] = true;
            que.push(nx);
            dist[nx] = dist[cur]+1;
            pre[nx] = cur; // 이전 인덱스를 저장해둠
            if(nx == k) { // nx == k 라면 마지막 연산이므로 ans 저장
                ans = dist[nx];
                break;
            }
        }
    }
    if(n==k) { // n == k이면 안 움직임
        cout << 0 << '\n' << n;
        return 0;
    }
    cout << ans << '\n';
    stack<int> result; // 움직인 위치를 저장하기 위한 stack

    result.push(k); // 스택이므로 젤 마지막인 k 부터 넣음
    for(int i=0;i<ans;i++){
        result.push(pre[k]); // k부터 역순으로 push
        k = pre[k];
    }
    while(!result.empty()){ // 순서대로 pop
        cout << result.top() << " ";
        result.pop();
    }
    return 0;
}