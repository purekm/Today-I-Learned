#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int arr[5001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    long long minimum = 3000000001;
    long long result1, result2, result3;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    
    for (int i=0; i<n-2; i++) {
        for (int j= i+1; j<n-1; j++) {
            long long sum = arr[i] + arr[j];
            int start = j + 1;
            int end = n - 1;
            
            while (start <= end) {
                int mid = (start+end)/2;
                long long total = sum+arr[mid];
                
                if (abs(total) < abs(minimum)) {
                    minimum = total;
                    result1 = i;
                    result2 = j;
                    result3 = mid;
                }
                
                if (total < 0) {
                    start = mid+1;
                } else {
                    end = mid-1;
                }
            }
        }
    }
    
    cout << arr[result1] << " " << arr[result2] << " " << arr[result3];
    return 0;
}
