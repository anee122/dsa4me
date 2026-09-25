#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n,k;
int a[21];

void backtrack(int pos){
    if(pos > k){
        for(int i = 1;i <= k;i++){
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }

    for(int j = a[pos-1]+1;j<=n-k+pos;j++){
        a[pos] = j;
        // cout << pos << " " << a[pos] << " ";
        backtrack(pos+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k;
    
    backtrack(1);

    return 0;
}