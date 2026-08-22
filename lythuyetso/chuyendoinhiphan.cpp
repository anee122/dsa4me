#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;cin >> n;
    vector<int> bin;
    int a;

    if(n==0) cout << 0;
    else if(n==1) cout << 1;
    while(n > 0){
        a=n%2;
        bin.push_back(a);
        n/=2;
    }
    reverse(bin.begin(),bin.end());

    for(auto x:bin) cout << x;
}