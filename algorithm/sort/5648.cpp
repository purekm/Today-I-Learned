#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector <long long> arr;
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        reverse(s.begin(),s.end());
        arr.push_back(atoll(s.c_str()));
    }
    sort(arr.begin(),arr.end());
    for(int i=0;i<n;i++){
        cout << arr[i] << '\n';
    }
    return 0;
}