#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    for(int k=0;k<t;k++){
        int n;
        cin >> n;
        vector<int> vec(n+1);
        vector<int> copy(n+1);
        vector<int> result;
        int maxi = 0;
        for(int i=0;i<n;i++) {
            cin >> vec[i];
            if(maxi<vec[i]) maxi = vec[i];
        }
        vec[n] = 10000;
        copy = vec;
        sort(copy.begin(),copy.end());
        int idx = n-1;
        int cnt = 0;
        // while(cnt==0 && copy != vec){
        //     if(vec[maxi-1] != maxi){
        //         cnt++;
        //         auto it = find(vec.begin(),vec.end(),maxi)-vec.begin();
        //         int temp = vec[n];
        //         vec[n] = vec[it];
        //         vec[it] = temp;
        //         idx = it;
        //         result.push_back(idx+1);
        //     }else {
        //         maxi--;
        //     }
        // }
        for(int i=n;i>0;i--){
            if(vec[i] != i){
                int temp = vec[i];
                vec[i] = vec[idx];
                vec[idx] = temp;
            }
        }
        while(copy != vec){
            cnt++;
            if(vec[idx] != idx+1) {
                auto it = find(vec.begin(),vec.end(),idx+1)-vec.begin();
                int temp = vec[idx];
                vec[idx] = vec[it];
                vec[it] = temp;
                idx = it;
                result.push_back(idx+1);
            }else
                idx--;
            // for(auto e : vec) cout << e << " ";
            // cout << '\n';
        }
        cout << result.size() << '\n';
        for(auto e:result) cout << e << " ";
        cout << '\n';
    }
    
    return 0;
}