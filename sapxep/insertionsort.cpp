#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int a[],int n){
    for(int i = 0;i < n;i++){
        int pos = i-1;x = a[i];
        while(pos >= 0 && a[pos]>=x){
            a[pos+1] = a[pos];
            --pos;
        }
        a[pos+1] = x;
    }
}

