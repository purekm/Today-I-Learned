#include <iostream>
#include <array>
#include <cmath> //올림 사용하기위해서 넣음

using namespace std;

int main(){
    int num=0,max=0;
    cin >> num;
    float result[10] = {0,}; //숫자당 나온 횟수를 배열에 저장
    string ans = to_string(num);
    for(int i=0;i<ans.size();i++){
        result[ans.at(i)-'0']++;
    }
    result[6] = ceil((result[6]+result[9])/2); // 올림 해줌
    result[9] = 0;
    for(int i=0;i<9;i++){
        if(max < result[i]) max = result[i];
    }
    cout << max;
    return 0;
}
