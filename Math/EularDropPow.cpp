#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#define ll long long
using namespace std;
ll phi(ll n) {//欧拉函数 
	ll ans = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans -= ans / i;//遇到质因数,即X*1/pi
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1)//若n不为1，则还剩下一位质因子
	ans -= ans / n;
	return ans;
}
ll fastpow(ll a, ll b, ll m) {//快速幂 
	ll ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = ans * a % m;
		}
		a = a * a % m;
		b >>= 1;
	}
	return ans;
}
ll eulerDropPow(ll a,char b[],ll c) {//欧拉降幂 
	ll eulerNumbers = phi(c);//模数c降幂 
	ll descendingPower = 0;
	for (ll i = 0, len = strlen(b); i < len; ++i) {
		descendingPower = (descendingPower * 10 + b[i] - '0') % eulerNumbers;
	}
	descendingPower += eulerNumbers-1;
	//descendingPower += eulerNumbers;应该是这样，只是这题要求a^(n-1) 
	return fastpow(a, descendingPower, c);
}
long long a=2;
long long c=1000000007;
char b[1000000000];
int main() {
	while(~scanf("%s",b)) {//a是底数，b是幂，c是模 
		cout<<eulerDropPow(a,b,c)<<endl; 
	}
}