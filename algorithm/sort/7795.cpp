#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
bool compare(string a,string b){
    if(a.length() == b.length()){
        return a < b;
    }else return a.length()< b.length();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        int n,m;
        cin >> n >> m;
        vector<int> a;
        vector<int> b;
        for(int j=0;j<n;j++){
            int num;
            cin >> num;
            a.push_back(num);
        }
        for(int j=0;j<m;j++){
            int num;
            cin >> num;
            b.push_back(num);
        }
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        int start = 0;
        int cnt = 0;
        int result = 0;
        for(int j=0;j<n;j++){
            for(int l=start;l<m;l++){
                if(a[j]==a[j-1]&&j>0) continue;
                if(a[j]>b[l]) {
                    start++;
                }else break;
            }
            result += start;
        }
        cout << result << '\n';
    }
    return 0;
}