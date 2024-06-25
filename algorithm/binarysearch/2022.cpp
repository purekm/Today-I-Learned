#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    double x,y,c;
    cin >> x >> y >> c;
    double start = 0;
    double end = min(x,y);
    double result = 0;
    while(end-start > 0.0009){
        double mid = (start+end)/2.0;
        double h1 = sqrt(x*x-mid*mid);
        double h2 = sqrt(y*y-mid*mid);
        if(c>((h1*h2)/(h1+h2))){
            end = mid;
        }else{
            result = mid;
            start = mid;
        }
    }
    printf("%.3f\n",result);
    return 0;
}
