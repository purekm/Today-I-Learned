#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;
int main(){
  int n;
  cin >> n;
  for(int i=0; i<n; i++){
    list<char> lt;
    string s;
    cin >> s;
    
    auto iter = lt.begin();
    
    for(auto e : s){
      switch(e){
        case '<':
          if(iter != lt.begin()) iter--;
          break;
        case '>':
          if(iter != lt.end()) iter++;
          break;
        case '-':
          if(iter != lt.begin()) iter = lt.erase(--iter);
          break;
        default :
          iter = lt.insert(iter,e);
          iter++;
          // for(auto e : lt) cout << e;
          // cout <<'\n';
          break;
      }
    }
    for(auto e : lt) cout << e;
    cout <<'\n';
  }
  return 0;
}