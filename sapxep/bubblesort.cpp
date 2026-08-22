#include <bits/stdc++.h>
using namespace std;

void bubble_sort(int a[],int n){
    for(int i = 0;i < n-1;i++){
        bool ok = false;
        for(int j = 0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                ok = true;
                swap(a[j],a[j+1]);
            }
        }
        if(!ok) break;
    }
}