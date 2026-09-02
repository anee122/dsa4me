#include <bits/stdc++.h>
using namespace std;

int X[1001],n;
bool ok;

void khoitao(){
    for(int i = 1;i <= n;i++){
        X[i] = 0;
    }
}

void sinh(){
    int i = n;
    while(i <= 1 && X[i]==1){
        X[i] == 0;
        --i;
    }
    if(i == 0) ok = false;
    else X[i] = 1;
}


int main(){
    cin >> n;
    khoitao();
    ok = true;

    while(ok){
        for(int i = 1;i <= n;i++){
            cout << X[i] << " ";
        }
        cout << endl;
        sinh();
    }

    return 0;
}