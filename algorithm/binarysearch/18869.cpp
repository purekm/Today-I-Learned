#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int binary_search(vector<int>& vec, int value) {
    int low = 0;
    int high = vec.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (vec[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int m, n;
    cin >> m >> n;
    vector<vector<int>> vec1(m, vector<int>(n, 0));
    vector<vector<int>> vec2(m, vector<int>(n, 0));
    vector<vector<int>> result(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> vec1[i][j];
            vec2[i][j] = vec1[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        sort(vec1[i].begin(), vec1[i].end());
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = binary_search(vec1[i], vec2[i][j]);
        }
    }

    int cnt = 0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (result[i] == result[j]) cnt++;
        }
    }

    cout << cnt << "\n";
    return 0;
}
