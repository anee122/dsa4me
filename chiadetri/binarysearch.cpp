#include <bits/stdc++.h>
using namespace std;
#define ll long long

int Binary_Search (int A[],int n,int X){
    int low = 1;
    int high = n;
    int mid;
    while(low <= high){
        mid = (low+high)/2;

        if(X>A[mid]){
            low = mid + 1;
        }
        else if(X < A[mid]){
            high = mid - 1;
        }
        else return(mid);
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 7;
    int a = {1,2,3,4,5,6,7};
    int X = 3;
    int test = Binary_Search(a,n,X);

    cout << test << endl;
    return 0;
}