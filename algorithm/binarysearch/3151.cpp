#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> vec(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    sort(vec.begin(), vec.end());
  
    long long result = 0;
    for(int i=0; i<n-1;i++) {
        for(int j=i+1; j<n; j++) {
            int sum = vec[i] + vec[j];
            int key = -sum;
            int start = j+1;
            int end = n-1;
            while (start <= end) {
                int mid = (start + end) / 2;
                if (vec[mid] == key) {
                    result++;
                    break;
                } else if (vec[mid] < key) {
                    start = mid+1;
                } else {
                    end = mid-1;
                }
            }
        }
    }
    cout << result;
    return 0;
}
