#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int arr[101];
    int hole,n;
    int cnt = 0;
    cin >> hole >> n;
    int multitap[101] ={0,};
    for(int i=0;i<n;i++) cin >> arr[i];
    for(int i=0;i<n;i++){
        bool check = false;
        for(int j=0;j<hole;j++){ // 이미 멀티탭에 있는 경우
            if(multitap[j] == arr[i]) {
                check = true;
                break;
            }
        }
        if(check) continue;

        for(int j=0;j<hole;j++){ // 빈칸이 있는 경우
            if(multitap[j]==0){ //멀티탭에 빈칸이 있는 경우
                multitap[j] = arr[i];
                check = true;
                break;
            }
        }
        if(check) continue;

        int last = -1;
        int index = -1;
        for(int j=0;j<hole;j++){ //가장 늦게 쓸 아이템을 빼기
            int pos = 0;
            for(int l=i+1;l<n;l++){
                if(multitap[j]==arr[l]){
                    break;
                }
                pos++;
            }
            if(pos>last) {
                last = pos;
                index = j;
            }
        }
        multitap[index] = arr[i]; //다음꺼로 변경
        cnt ++;
    }
    cout << cnt;
    
    return 0;
}