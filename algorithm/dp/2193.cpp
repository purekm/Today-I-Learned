#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main(){
    int n;
    cin >> n;
    long long binary[91];
    binary[1] = 1;
    binary[2] = 1;
    for(int i=3;i<=n;i++){
        binary[i] = binary[i-2] + binary[i-1];
    }
    cout << binary[n];

    
    return 0;
}