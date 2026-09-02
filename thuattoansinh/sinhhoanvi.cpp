#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n,X[1001];
bool ok;

void khoitao(){
    for(int i = 1;i<=n;i++){
        X[i] = i;
    }
}

void sinh(){
    int i = n-1;
    while(i >= 1 && X[i]>X[i+1]){
        --i;
    }
    if(i == 0) ok = false;
    else{
        int j = n;
        while(X[j]<X[i]) --j;
        swap(X[i],X[j]);
        sort(X+i+1,X+n+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    khoitao();
    ok = true;
    while(ok){
        for(int i = 1;i<=n;i++){
            cout << X[i] << " ";
        }
        cout << endl;
        sinh();
    }

    return 0;
}