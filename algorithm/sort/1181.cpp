#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
bool compare(string a,string b){
    if(a.length() == b.length()){
        return a < b;
    }else return a.length()< b.length();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> arr;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        arr.push_back(s);
    }
    
    sort(arr.begin(),arr.end(),compare);
    arr.erase(unique(arr.begin(),arr.end()),arr.end());
    for(int i=0;i<arr.size();i++){
        cout << arr[i] << '\n';
    }
    return 0;
}