#include <bits/stdc++.h>
using namespace std;
#define ll long long

int X[1001],n,k;
bool ok;

void khoitao(){
    for(int i = 1;i <= k;i++){
        X[i] = i;
    }
}

void sinh(){
    int i = n;
    while(i >= 1 && X[i]=n-k+i){
        --i;
    }
    if (i == 0) ok = false;
    else{
        X[i]++;
        for(int j = i+1;j<=k;j++){
            X[j] = X[j-1] + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    khoitao();
    ok = true;
    while(ok){
        for (int i = 1;i<=k;i++){
            cout << X[i] << " ";
        }
        cout << endl;
        sinh();
    }

    return 0;
}