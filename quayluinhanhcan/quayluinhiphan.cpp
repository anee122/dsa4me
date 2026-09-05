#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
char ans[21];

void backtrack(int pos){
    if(pos > n){
        for(int i = 1;i <= n;i++){
            cout << ans[i];
        }
        cout << endl;
        return;
    }

    for(char i = '0';i <= '1';i++){
        ans[pos]= i;
        backtrack(pos + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    backtrack(1);
    return 0;
}