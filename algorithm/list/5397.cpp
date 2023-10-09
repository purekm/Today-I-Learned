#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;
int main(){
    int n = 0;
    cin >> n;
    for(int i =0;i<n;i++){
        list<char> arr={};
        auto cursur = arr.begin();
        string s;
        cin >> s;
        for(auto c:s){
            if (c == '<') {
        if (cursur != arr.begin()) cursur--;
      }
      else if (c == '>') {
        if (cursur != arr.end()) cursur++;
      }
      else if (c == '-') {
        if (cursur != arr.begin()) {
          cursur--;
          cursur = arr.erase(cursur);
        }
      }
      else
        arr.insert(cursur, c); 
        }
         for(auto c:arr){
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}