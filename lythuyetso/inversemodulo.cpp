#include <bits/stdc++.h>
using namespace std;

//giai thuat euclid mo rong
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

//modulo
//cho so A,M. Tim so B thoa man pt :(A*B)/M = 1
//khi do B se duoc goi la nghich dao modulo cua A voi modulo M
//Dieu kien xay ra: gcd(A,M) = 1 ; B thuoc [1,M-1]

//voi cach lam dua vao giai thuat euclid mo rong
// ax + by = gdc(a,b)
// a,m : (a*b)/m = 1
// -> ax + my = 1
// -> (ax + my)%m = 1%m;
// -> ax % m = 1%m -> x:nghich dao modulo cua a

int modulo_inverse(int a,int m){
    extended_gcd(a,m);
    return (x%m + m)%m;
}

//voi cach pho thong
int modulo_inverse(int a,int m){
    for(int i = 1;i<m;i++){
        if (a*i%m==1) return i;
    }
}