#include <bits/stdc++.h>
using namespace std;
#define ll long long;

ll nCk (ll n,ll k){
	ll res = 1;
	k = min (k, n-k);
	for (int i = 0;i < k;i++){
		res *= (n-i);
		res /= (i+1);
	}
	return res;
}

//tinh to hop chap k cua n dua tren quy hoach dong
ll C[1001][1001];
void init(){
	for (int i =0;i <= 1000;i++){
		for(int j =0;j<=i;j++){
			if(j==0||j==i) C[i][j] = 1;
			else {
				C[i][j] = C[i-1][j-1] + C[i-1][j];
				C[i][j] %= (1e9 + 7);
			}
		}
	}
}