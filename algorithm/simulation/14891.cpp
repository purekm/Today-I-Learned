#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string.h>
#include <cmath>
using namespace std;

vector<deque<int>> gear(5);
bool check[5];

void rotate(int g,int d){
    if(d == 1){
        int temp = gear[g].back();
        gear[g].pop_back();
        gear[g].push_front(temp);
    }else if(d == -1){
        int temp = gear[g].front();
        gear[g].pop_front();
        gear[g].push_back(temp);
    }
}

void rotation(int g,int d){
    check[g] = true;
    if(g-1>0 && !check[g-1]){
        if(d != 0){
            if(gear[g][6] == gear[g-1][2]) rotation(g-1,0);
            else rotation(g-1,-d);
        }else rotation(g-1,0);
    }
    if(g+1<=4 && !check[g+1]){
        if(d != 0){
            if(gear[g][2] == gear[g+1][6]) rotation(g+1,0);
            else rotation(g+1,-d);
        }else rotation(g+1,0);
    }
    rotate(g,d);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i=1;i<=4;i++){
        for(int j=0;j<8;j++){
            char n;
            cin >> n;
            gear[i].push_back(n-'0');
        }
    }
    int t,gear_num,dir,result;
    result = 0;
    cin >> t;
    for(int i=0;i<t;i++){
        memset(check,false,sizeof(check));
        cin >> gear_num >> dir;
        rotation(gear_num,dir);
    }
    if(gear[1][0] == 1) result += 1;
    if(gear[2][0] == 1) result += 2;
    if(gear[3][0] == 1) result += 4;
    if(gear[4][0] == 1) result += 8;
    cout << result <<'\n'; 

    return 0;
}