#include <bits/stdc++.h>
using namespace std;

//cho so N va so nguyen to k. Tim x sao cho N! chia het cho k voi x max

int degree (int n,int k){
    int ans= 0;
    for (int i = 0;i <= n;i++){
        int m = i;
        while (m%k == 0){
            ans++;
            m/=k;
        }
    }
    return ans;
}