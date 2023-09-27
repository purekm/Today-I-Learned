#include <iostream>
#include <array>

using namespace std;

int main(){
    int a,b,c,num;
    int result[10] = {0,};
    cin >> a;
    cin >> b;
    cin >> c;
    num = a*b*c;
    string ans = to_string(num);
    for(int i=0;i<ans.size();i++){
        result[(int)(ans.at(i)-'0')]++;
    }

    for(int i=0;i<10;i++){
        cout << result[i]<<'\n';
    }

    return 0;
}