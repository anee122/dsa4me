#include <bits/stdc++.h>
using namespace std;
#define ll long long;

ll binpow (ll a,ll b){
	if(b == 0) return 1;
	ll x = binpow(a,b/2);
	if(b%2 == 1) return x*x*a;
	else return x*x;
}
