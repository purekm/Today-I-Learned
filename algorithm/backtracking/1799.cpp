#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
int n,cnt,cnt2,temp,temp2;
int board[11][11];
bool leftd[22];
bool rightd[22];

void recur(int check){ //백
    if(temp<cnt) temp = cnt;
    for(int i=check;i<n*n;i++){
        int x = i/n;
        int y = i%n;
        if((x+y)%2==1) continue;
        if(board[x][y] == 0 ) continue;
        if(rightd[x+y] || leftd[y-x+n-1]) continue;
        rightd[x+y] = true;
        leftd[y-x+n-1] = true; 
        cnt++;
        recur(i+1);
        rightd[x+y] = false;
        leftd[y-x+n-1] = false; 
        cnt--;
    }
}
void recur2(int check){ //흑
    if(temp2<cnt2) temp2 = cnt2;
    for(int i=check;i<n*n;i++){
        int x = i/n;
        int y = i%n;
        if((x+y)%2==0) continue;
        if(board[x][y] == 0 ) continue;
        if(rightd[x+y] || leftd[y-x+n-1]) continue;
        rightd[x+y] = true;
        leftd[y-x+n-1] = true; 
        cnt2++;
        recur2(i+1);
        rightd[x+y] = false;
        leftd[y-x+n-1] = false; 
        cnt2--;
    }
}

int main(){
    cnt = 0;
    cnt2 = 0;
    temp = 0;
    temp2 = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> board[i][j];
        }
    }
    recur(0);
    recur2(0);
    // cout << temp << ' ' << temp2;
    temp+=temp2;
    cout << temp;
    return 0;
}