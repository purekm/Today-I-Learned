#include<iostream>

using namespace std;
int a;
long long recur(int b,int c){
    long long sol;
    if(b==1) return a%c;
    sol = recur(b/2,c)%c;
    if(b%2==0){
        return sol*sol%c;
    }else{
        return sol*sol%c*a%c;
    }
}

int main(){
    int b,c;
    cin >> a >> b >> c;
    long long result = recur(b,c);
    cout << result;
    return 0;
}