#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000;

bool nt[maxn + 1];
void sang(){
	for (int i = 0;i<=maxn;i++){
		nt[i] = true;
	}

	nt[0] = nt[1] = false;
	for (int i = 2;i<=maxn;i++){
		if(nt[i]){
			for (j = i*i;j<=maxn;j++){
				nt[j] = false;
			}
		}
	}
}