#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
int a[21],Visited[21];

void backtrack(int pos){
    if(pos > n){
        for(int i = 1;i <= n;i++){
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }

    for(int i = 1;i <= n;i++){
        if(!Visited[i]){
            a[pos] = i;
            Visited[i] = 1;
            backtrack(pos+1);
            Visited[i] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(Visited,0,sizeof(Visited));
    cin >> n;
    backtrack(1);

    return 0;
}