#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
int main(){
    list<int> lt;
    list<int> result;
    int n,k;
    int num = 1;
    auto iter = lt.begin();
    cin >> n >> k;

    for(int i=1;i<=n;i++) lt.push_back(i);

    while(!lt.empty()){
        for(int i=0; i<k-1;i++){
            lt.push_back(lt.front());
            lt.pop_front();
        }
        result.push_back(lt.front());
        lt.pop_front();
    }
    cout << '<';
    while(!result.empty()){
        if(result.size()==1) cout << result.front();
        else cout << result.front() << ", ";
        result.pop_front();
    }
    cout << '>';
    
    return 0;
}