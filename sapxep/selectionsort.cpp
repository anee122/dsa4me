#include <bits/stdc++.h>
using namespace std;

void selection_sort(int a[],int n){
    for(int i = 0;i < n-1;i++){
        int min_idx = i;
        for(int j = i+1;j<n;j++){
            if(a[min_idx] > a[j]) min_idx = j;
        }
        swap(a[min_idx],a[i]);  
    }
}