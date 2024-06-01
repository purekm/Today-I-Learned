#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;
set<int> plugin;

int main(){
    vector<int> vec;
    int arr[101];
    int hole,n;
    cin >> hole >> n;
    for(int i=1;i<=n;i++){
        int a;
        cin >> a;
        if(i<=hole) {
            plugin.insert(a);
            continue;
        }
        arr[i] = a;
        
    }
    for(int i=hole;i<=n;i++){
        plugin.find(arr[i]);
    }

    
    return 0;
}