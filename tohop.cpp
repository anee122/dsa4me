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