#include <bits/stdc++.h>
using namespace std;

int x,y,g;

void extended_gcd (int a, int b){
    if(b==0) {
        x = 1; y = 0;
        y = a;
    }
    else{
        extended_gcd(b,a%b);
        int tmp = x;
        x = y;
        y = tmp - a/b*y;
    }
}