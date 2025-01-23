#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 65;

int n;
ll b[N];
ll tmp[N];
bool flag;

void ins(ll x) //插入数字，获取线性基
{
	for(int i = 62; i >= 0; i --) {
		if(x >> i & 1) {
			if(!b[i]) {
				b[i] = x;
				return;
			}
			else x ^= b[i];
		}
	}
	flag = true;
}

ll find_max() //找到能被表示出来的最大值
{
	ll ans = 0;
	for(int i = 62; i >= 0; i --) {
		ans = max(ans, ans ^ b[i]);
	}
	return ans;
}

ll find_min() //找到能被表示出来的最小值
{
	for(int i = 0; i <= 62; i ++) {
		if(b[i]) {
			return b[i];
		}
	}
}

ll get_kth(ll k) //找到第k小的能被表示出来的数
{
	ll res = 0;
	int cnt = 0;
	k -= flag;
	if(!k) return 0;
	for(int i = 0; i <= 62; i ++) {
		for(int j = i - 1; j >= 0; j --) {
			if(b[i] >> j & 1) b[i] ^= b[j];
		}
		if(b[i]) tmp[cnt++] = b[i];
	}
	if(k >= (1ll << cnt)) return -1;
	for(int i = 0; i < cnt; i ++) {
		if(k >> i & 1) {
			res ^= tmp[i];
		}
	}
	return res;
}

bool find_x(ll x) //x是否能被线性基表示出来
{
	for(int i = 62; i >= 0; i --) {
		if(x >> i & 1) {
			if(!b[i]) return false;
			x ^= b[i];
		}
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		ll x;
		scanf("%lld", &x);
		ins(x);
	}
	ll ans = find_max();
	printf("%lld\n", ans);
	return 0;
}