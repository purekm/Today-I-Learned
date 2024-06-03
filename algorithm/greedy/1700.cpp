#include <iostream>
#include <vector>

using namespace std;

int main(){
    int arr[101];
    int hole, n;
    int cnt = 0;
    cin >> hole >> n;
    vector<int> multitap(hole, 0); 
    for(int i = 0; i < n; i++) cin >> arr[i];

    for(int i = 0; i < n; i++) {
        bool check = false;

        // 이미 멀티탭에 있는 경우
        for(int j = 0; j < hole; j++) {
            if(multitap[j] == arr[i]) {
                check = true;
                break;
            }
        }
        if(check) continue;

        // 빈칸이 있는 경우
        for(int j = 0; j < hole; j++) {
            if(multitap[j] == 0) {
                multitap[j] = arr[i];
                check = true;
                break;
            }
        }
        if(check) continue;

        int last = -1;
        int index = -1;

        // 가장 늦게 사용할 아이템을 찾기
        for(int j = 0; j < hole; j++) {
            int pos = n; 
            for(int l = i + 1; l < n; l++) {
                if(multitap[j] == arr[l]) {
                    pos = l;
                    break;
                }
            }
            if(pos > last) {
                last = pos;
                index = j;
            }
        }
        multitap[index] = arr[i];
        cnt++;
    }
    cout << cnt;
    
    return 0;
}