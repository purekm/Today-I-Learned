#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int arr[4001][4];
vector<int> vec1;
vector<int> vec2;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    for(int i=0; i<n; i++) 
        for(int j=0; j<4;j++)
            cin >> arr[i][j];

    for(int i=0; i<n; i++){
        for(int j=0;j<n;j++){
            vec1.push_back(arr[i][0]+arr[j][1]);
            vec2.push_back(arr[i][2]+arr[j][3]);
        }
    }
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    long long result = 0;
    for(int i=0; i<vec1.size(); i++){
        int key = -vec1[i];
        int start = lower_bound(vec2.begin(),vec2.end(),key)-vec2.begin();
        int end = upper_bound(vec2.begin(),vec2.end(),key)-vec2.begin();
        result += (end - start);
    }
    cout << result;
    return 0;
}
