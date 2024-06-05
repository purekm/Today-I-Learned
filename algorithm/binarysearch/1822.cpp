#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
int arra[500001];
int arrb[500001];
queue<int> result;


int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int a,b;
    int cnt = 0;
    cin >> a >> b;
    for(int i=0;i<a;i++) cin >> arra[i];
    for(int i=0;i<b;i++) cin >> arrb[i];
    sort(arra,arra+a);
    sort(arrb,arrb+b);
    for(int i=0;i<a;i++){
        int start = 0;
        int end = b-1;
        bool flag = false;
        while(end>=start){
            int mid = (start+end)/2;
            if(arrb[mid]==arra[i]){
                flag = true;
                break;
            }else if(arrb[mid]>arra[i]){
                end = mid-1;
            }else start = mid+1;
        }
        if(!flag){
            cnt++;
            result.push(arra[i]);
        }
    }
    cout << cnt << '\n';
    if(cnt>0){
        while(!result.empty()){
            cout << result.front() << " ";
            result.pop();
        }
    }
    return 0;
}