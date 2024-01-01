#include<iostream>
#include<queue>


using namespace std;
int a,cnt;
queue<int> que;
queue<int> que2;
void recur(int num,int from,int by,int to){
    if(num ==0) return;
    recur(num-1,from,to,by);
    que.push(from);
    que2.push(to);
    recur(num-1,by,from,to);
    cnt++;
}

int main(){
    int a;
    cin >> a;
    recur(a,1,2,3);
    cout << cnt <<'\n';
    while(!que.empty()){
        int f = que.front();
        int f2 = que2.front();
        que.pop();
        que2.pop();
        cout << f << " "<< f2 << '\n';
    }
    return 0;
}