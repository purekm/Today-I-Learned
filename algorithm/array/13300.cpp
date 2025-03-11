#include <iostream>
#include <array>
#include <vector>


using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> boy(7);
    vector<int> girl(7);
    int n,k;
    int room = 0;
    cin >> n >> k;
    for(int i=0; i < n; i++){
        int gender , grade;
        cin >> gender >> grade;

        if (gender == 0) girl[grade]++;
        else boy[grade]++;
    }

    for(int i=1; i<7;i++){
        if(boy[i]%k==0)
            room += boy[i]/k;
        else
            room += boy[i]/k+1;
    }
    for(int i=1; i<7;i++){
        if(girl[i]%k==0)
            room += girl[i]/k;
        else
            room += girl[i]/k+1;
    }
    cout << room;

    
    
    return 0;
}
/*  남 1 여 0 이니까  
남녀는 따로 써야해
학년수만큼 모아서 /2로 몫을 구하면 room 개수가 되는거잖아
그걸 다 더하면 되지 않을까?*/