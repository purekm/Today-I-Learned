#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
vector<int> arr; //1이상
vector<int> arr2; //0이하

int main(){
   int n;
   int cnt = 0;
   bool flag = false;
   bool flag2 = false;
   cin >> n;
   int sum = 0;
   
   for(int i=0;i<n;i++){
    int num;
    cin >> num;
    if(num>0) arr.push_back(num);
    else arr2.push_back(num);
   }
   sort(arr.begin(),arr.end());
   sort(arr2.begin(),arr2.end());

   if(arr.size()%2==0) flag = true; //짝수면 true
   if(arr2.size()%2==0) flag2 = true; //짝수면 true
   if(!arr.empty()){
    for(int i= arr.size()-1;i>0;i-=2){
        if(arr[i]==1 || arr[i-1]==1) sum+=arr[i]+arr[i-1];
        else sum+= arr[i]*arr[i-1]; 
    }
   }
   if(!arr2.empty()){
    for(int i=0;i<arr2.size()-1;i+=2){
        sum+=arr2[i]*arr2[i+1];
    }
   }
   if(!flag) sum +=arr.front();
   if(!flag2) sum += arr2.back();
   cout << sum;

    
    return 0;
}