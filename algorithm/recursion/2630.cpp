#include<iostream>
#include<cmath>

using namespace std;
int k,n,r,c;
string s;
int board[2200][2200];
int result[2];
bool check = false;
void recur(int k,int x,int y){
    if(k<1) return;
    check = true;
    for(int i=y;i<y+k;i++){
        for(int j=x;j<x+k;j++){
            if(board[y][x] != board[i][j]){
                check = false; break;
            }
        }
    }
    int size = k/2;
    if(!check){
        cout << '(';
        recur(size,x,y);
        recur(size,x+size,y);
        recur(size,x,y+size);
        recur(size,x+size,y+size);
        cout << ')';
        return;
    }
    cout << board[y][x];
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> s;
        for(int j=0;j<n;j++) board[i][j] = s[j]-'0';
    }
    recur(n,0,0);
    cout << '\n';
    return 0;
}