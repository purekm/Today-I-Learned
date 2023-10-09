#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int num = 0,result = 0,cnt=0;
    cin >> num;
    vector<int> arr(num);
    for(int i=0;i<num;i++){
        cin >> arr[i];
    }
    cin >> result;
    sort(arr.begin(),arr.end());
    int left = 0;
    int right = num-1;
    while(left<right){
        if(arr[left]+arr[right] == result){
            cnt++;
            left++;
            right--;
        }else if(arr[left]+arr[right]>result){
            right--;
        }else{
            left++;
        }
    }
    cout << cnt ;
    return 0;
}