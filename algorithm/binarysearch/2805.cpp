#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;
int tree[1000001];

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> tree[i];
    sort(tree,tree+n);

    int start = 0;
    int end = tree[n-1];
    long long sum = 0;
    long long result = 0;

    while(end >= start){
        sum = 0;
        int mid = (start+end)/2;
        for(int i=0;i<n;i++){
            if(tree[i]>mid) sum += tree[i]-mid;
        }
        if(sum >= m){
            result = mid;
            start = mid+1;
        }else 
            end = mid-1;
    }
    cout << result <<'\n';

    return 0;
}