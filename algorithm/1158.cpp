#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
int main(){
    int n,k;
    cin >> n >>k;
    list<int> arr;
    list<int> result;
    for(int i=1;i<=n;i++){
        arr.push_back(i);
    }
    int m = 1; // 3번째 숫자인지 확인을 위한 num
    while(!arr.empty()){
        if(m == k){
            result.push_back(arr.front());
            arr.pop_front();
            m=1;
        }else{
            arr.push_back(arr.front());
            arr.pop_front();
            m++;
        }
    }
    cout<< '<';
    for(int i=0;i<n;i++){
        if(i==n-1){
            cout <<result.front() <<">";
        }else{
            cout <<result.front() <<", ";
        }
        result.pop_front();
    }
    return 0;
}