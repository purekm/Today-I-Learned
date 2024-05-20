#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int color[1005][3];

int main(){
    int n;
    int minn = 1000000;
    cin >> n;
    for(int i=1;i<=n;i++){
       cin >> color[i][0] >> color [i][1] >> color[i][2];
    }
    for(int i=0;i<3;i++){
        int d[1005][3];
        for(int j=0; j<3; j++){
            if(j==i) d[1][j] = color[1][j];
            else d[1][j] = 10000000;
        }
        for(int j=2;j<=n;j++){
            d[j][0] = min(d[j-1][1],d[j-1][2]) + color[j][0]; 
            d[j][1] = min(d[j-1][0],d[j-1][2]) + color[j][1];
            d[j][2] = min(d[j-1][0],d[j-1][1]) + color[j][2];
        }
        for(int j=0;j<3;j++){
            if(j == i) continue;
            else minn = min(minn,d[n][j]);
        }
    }
    cout << minn;
    

    
    // d[n][0] = min(d[n-1][1]+b[n],d[n-1][2]+g[n]);
    // d[n][1] = min(d[n-1][2]+r[n],d[n-1][0]+b[n]);
    // d[n][2] = min(d[n-1][0]+g[n],d[n-1][1]+r[n]);
    return 0;
}