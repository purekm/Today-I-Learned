#include <bits/stdc++.h> 
using namespace std;

string board[12];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int check[12][6];

int totalNum = 1;

void fallFunc(void);
void showboard(void);

// 제거 하기 전에 미리 탐색해서 주변에 동일한 색이 몇개있는지 출력하는 함수 
int checkNum (int a, int b) {
    int totNum = 0;
    stack <pair<int, int>> q;
    q.push({a,b});
    while (!q.empty()){
        pair<int, int> cur = q.top(); q.pop();
        check[cur.first][cur.second] = 1;
        totNum++;
        char curChar = board[cur.first][cur.second];
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(nx < 0|| ny < 0 || nx >= 12 || ny >= 6) continue;
            if(check[nx][ny] != 0) continue;
            if(board[nx][ny] != curChar || board[nx][ny] == '.') continue;
            
            q.push({nx,ny});
        }
    }
    for(int i = 0 ; i < 12 ; i++) fill(check[i], check[i] + 6, 0);
    return totNum;
}
// 배열을 전부 돌면서 제거 할거 제거해주는 함수 
void removeFunc (void) {
    int isRemoved = 0;
    for(int i = 0 ; i < 12 ; i++) {
        for(int j = 0 ; j < 6 ; j++) {
            if(board[i][j] == '.') continue;
            if(checkNum(i,j) < 4 ) continue;
            isRemoved = 1;
            stack <pair<int, int>> q;
            q.push({i,j});
            while (!q.empty()){
                pair<int, int> cur = q.top(); q.pop();
                check[cur.first][cur.second] = 1;
                char curChar = board[cur.first][cur.second];
                board[cur.first][cur.second] = '.';
                for (int dir = 0; dir < 4; dir++) {
                    int nx = cur.first + dx[dir];
                    int ny = cur.second + dy[dir];
                    if(nx < 0|| ny < 0 || nx >= 12 || ny >= 6) continue;
                    if(check[nx][ny] != 0) continue;
                    if(board[nx][ny] != curChar || board[nx][ny] == '.') continue;
                    q.push({nx,ny});
                }
            }
            for(int i = 0 ; i < 12 ; i++) fill(check[i], check[i] + 6, 0);
        }
    }
    if(isRemoved) totalNum += 1;
    // showboard();
    // cout << totalNum - 1<< '\n';
    if (isRemoved) fallFunc();
}

// 제거한 후 남은 요소들을 밑으로 내려주는 함수 
void fallFunc(void) {
    int isFall = 0;
    for(int col = 0 ; col < 6 ; col++) {
        int startP = 11;
        for(int i = 11 ; i >= 0 ; i--) {
            if (board[i][col] != '.'){
                startP--;
                continue;
            }
            break;
        }
        int newS = startP  ;
        for (int i = startP ; i >= 0 ; i--) {
            if (board[i][col] == '.') continue;
            isFall = 1;
            board[newS--][col] = board[i][col];
            board[i][col] = '.';
        }
        if (checkNum(startP,col) < 4) continue;
    }
    // showboard();
    if (isFall) removeFunc();

}

void showboard(){
    cout << '\n';
    for(int i = 0 ; i < 12 ; i++ ){
        for(int j = 0 ; j < 6 ; j++ ){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0 ; i < 12 ; i++) cin >> board[i];
    removeFunc();
    cout << totalNum - 1 <<'\n';
    return 0;
}