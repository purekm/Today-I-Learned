#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


vector<pair<int,int>> day;


int calculate(int month){
    int sum = 0;
    if(month == 1) sum = 0;
    else if(month == 2) sum = 31;
    else if(month == 3) sum = 59;
    else if(month == 4) sum = 90;
    else if(month == 5) sum = 120;
    else if(month == 6) sum = 151;
    else if(month == 7) sum = 181; 
    else if(month == 8) sum = 212;
    else if(month == 9) sum = 243;
    else if(month == 10) sum = 273;
    else if(month == 11) sum = 304;
    else if(month == 12) sum = 334;
    return sum;
}
int main(){
    int n,minday,maxday;
    minday = 365; //끝나는 날
    maxday = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        int sday,smonth,lday,lmonth,sum1,sum2;
        cin >> smonth >> sday >> lmonth >> lday;
        sum1 = calculate(smonth) + sday;
        sum2 = calculate(lmonth) + lday;
        if(maxday< sum2) maxday = sum2;
        if(minday> sum1) minday = sum1;
        day.push_back({sum2,sum1}); //끝나는날 시작하는날 순서로 넣음
    }
    if(maxday <334 ||  minday > 60){
        cout << 0;
        return 0;
    }
    sort(day.begin(),day.end());
    
    int start = 60;
    int cnt = 0;
    while(true){
        if(start>334) break; // 끝나는 지점
        int k = start;
        for(int i=0;i<n;i++){
            if(day[i].second <= start){
                if(day[i].first>k) k = day[i].first;
            }else continue;
        }
        
        if(k == start){
            cout << 0;
            return 0;
        }
        start = k;
        cnt++;
        // cout << start << ' ';
    }
    cout << cnt;


    return 0;
}