#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>


using namespace std;
string arr[1000];
int dx[8] = {1,1,1,0,0,-1,-1,-1};
int dy[8] = {1,0,-1,1,-1,1,0,-1};
int n,m,k;
unordered_map<string,int> map;
void bfs(int i, int j){
    queue<tuple<int,int,string>> que;
    string s;
    s += arr[i][j];
    map[s]++;
    que.push({i,j,s});
    while(!que.empty()){
        int x,y;
        string z;
        tie(x,y,z) = que.front();
        que.pop();
        
        for(int k=0;k<8;k++){
            int nx = (x+dx[k]+n)%n;
            int ny = (y+dy[k]+m)%m;
            string nz = z+arr[nx][ny];
            map[nz] ++;
            if(nz.length()<5) que.push({nx,ny,nz});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) bfs(i,j);
    }
    for(int i=0; i<k; i++){
        string s;
        cin >> s;
        cout << map[s] << '\n';
    }
    return 0;
}
