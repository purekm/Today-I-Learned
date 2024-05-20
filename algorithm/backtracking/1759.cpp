#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
int l,c,gat,con;
char arr[16];
char result[16];
bool visit[16];
queue<char> que;
void recur(int k,int start){
    if(k==l){
        for(int i=0;i<l;i++){
            if(result[i]=='a'||result[i]=='e'||result[i]=='i'||result[i]=='o'||result[i]=='u') gat++; // 모음 개수
            que.push(result[i]);
        }
        con = l - gat;
        if(gat>=1 && con>=2){
            while(!que.empty()) {
                cout << que.front();
                que.pop();
            }
            cout << '\n';
        }else{
            while(!que.empty()) que.pop();
        }
        gat = 0;
        con = 0;
    }
    for(int i=start; i<c;i++){
        if(visit[i]) continue;
        result[k] = arr[i];
        visit[i] = true;
        recur(k+1,i+1);
        visit[i] = false;
    }
}
int main(){
    cin >> l >> c;
    gat = 0;
    con = 0;
    for(int i=0; i<c; i++){
        cin >> arr[i];
    }
    sort(arr,arr+c);
    // for(int i=0; i<c; i++){
    //     cout << arr[i] << '\n';
    // }
    recur(0,0);


    return 0;
}