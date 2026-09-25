#include <bits/stdc++.h>
using namespace std;
#define ll long long

int Lower_Bound (int A[], int n, int X) {
    int low = 1;
    int high = n;
    int mid;
    int ans = -1; 

    while(low <= high) {
        mid = (low + high) / 2;

        if (A[mid] >= X) { 
            ans = mid;       
            high = mid - 1;  
        } 
        else { 
            low = mid + 1;
        }
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int a[1001];
    int X;
    cin >> n >> X;
    for(int i = 1;i <= n;i++) cin >> a[i];

    cout << Lower_Bound(a,n,X);
    
    
    return 0;
}