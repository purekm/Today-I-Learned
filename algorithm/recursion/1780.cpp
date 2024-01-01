#include<iostream>
#include<cmath>

using namespace std;
int k,n,r,c;
int board[2200][2200];
int result[3];
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
    int size = k/3;
    if(!check){
        recur(size,x,y);
        recur(size,x+size,y);
        recur(size,x,y+size);
        recur(size,x+size*2,y);
        recur(size,x,y+size*2);
        recur(size,x+size,y+size);
        recur(size,x+size,y+size*2);
        recur(size,x+size*2,y+size);
        recur(size,x+size*2,y+size*2);
    }else{
        if(board[y][x]==-1) result[2]++;
        else result[board[y][x]]++;
    }
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin >> board[i][j];
    }
    recur(n,0,0);
    cout << result[2] << '\n';
    cout << result[0] << '\n';
    cout << result[1] << '\n';
    return 0;
}