#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int arr[51][51];
bool clean[51][51];
int n,m,r,c,d;
int cnt = 0;
int direction;
void dfs(int x,int y,int sum){
    if(arr[x][y] == 0 &&!clean[x][y]) {
        clean[x][y] = true;
    }
    for(int i=1;i<=4;i++){
        d = (d+3)%4; 
        int nx = x+dx[d];
        int ny = y+dy[d];
        if(nx>=m||ny>=n||nx<0||ny<0) continue;
        if(arr[nx][ny] == 0 && !clean[nx][ny]) {
            dfs(nx,ny,sum+1);
        }
    }
    int nx = x-dx[d];
    int ny = y-dy[d];
    if(nx>=0&&ny>=0&&nx<=m&&ny<=n){
        if(arr[nx][ny]==0) dfs(nx,ny,sum);
        else{
            cout << sum;
            exit(0);
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    cin >> r >> c >> d;
    int cnt = 0;
    for(int i=0;i<n;i++) fill(clean[0],clean[51],false);

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) cin >> arr[i][j];
    
  
    
    dfs(r,c,1);
    
    return 0;
}