#include <bits/stdc++.h>
using namespace std;
#define ll long long;
const int MOD = 10e9 + 7;

// (A+B)%C = ((A%C)+(B%C))%C
// (A-B)%C = ((A%C)-(B%C))%C
// (A*B)%C = ((A%C)*(B%C))%C
// (A^B)%C = ((A%C)^B)%C
// (A/B)%C = ((A%C)*(B^-1))%C

//(A^B)%C
ll powMOD(ll a,ll b,ll c){
	ll res = 1;
	a %= c;
	for(int i = 1;i <= b;i++){
		res *= a;
		res %= c;
	}
	return res % c;
}
