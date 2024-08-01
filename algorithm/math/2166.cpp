#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<double,double>> vec(n);
    for(int i=0;i<n;i++){
        cin >> vec[i].first >> vec[i].second;
    }
    double sum = 0.0;
    for(int i=1;i<n-1;i++){
        sum += (vec[0].first*vec[i].second + vec[i].first*vec[i+1].second + vec[i+1].first*vec[0].second);
        double minus = (vec[i].first*vec[0].second + vec[i+1].first*vec[i].second + vec[0].first*vec[i+1].second);
        sum -= minus;
    }
    sum /= 2;
    cout << fixed;
    cout.precision(1);
    cout << abs(round(sum*10)/10);
    return 0;
}