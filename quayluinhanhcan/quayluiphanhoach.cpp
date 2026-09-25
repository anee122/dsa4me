#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n= 100;
int a[50],X[4] = {0,10,20,50};
int sum =0,cnt = 0;

void backtrack(int pos){
    if(sum >= n){
        if(sum == n){
            for(int i = 1;i<=pos-1;i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    for (int i = 1; i <= 3; i++) {

        if (pos == 1 || X[i] >= a[pos - 1]) {

            a[pos] = X[i];
            sum += X[i];
            backtrack(pos + 1);
            sum -= X[i];
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    backtrack(1);
    return 0;
}