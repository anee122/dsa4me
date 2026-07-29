#include <bits/stdc++.h>
using namespace std;

//Cho hai so a,b. Tim x va y thoa man phuong trinh:
//ax + by = gcd(a,b)
//ax + by = g <=> ay1 + b(x1 - a/b*y1) = g

int x,y,g;

void extended_gcd (int a, int b){
    if(b==0) {
        x = 1; y = 0;
        y = a;
    }
    else{
        extended_gcd(b,a%b);
        int tmp = x;
        x = y; //x=y1
        y = tmp - a/b*y; //y=x1-a/b*y1
    }
}