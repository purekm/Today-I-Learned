#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;
unordered_map<long long,long long> map;
long long n;
int p, q;
long long dp(long long num){
    if(map.count(num)) return map[num];
    map[num] = dp(num/p) + dp(num/q);
    return map[num];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> p >> q;
    map[0] = 1;
    
    cout << dp(n);
    return 0;
}
