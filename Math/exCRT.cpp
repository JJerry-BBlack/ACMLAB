ll excrt(ll k, ll *a, ll *r) {
	ll M = r[1], ans = a[1];
	for (int i = 2; i <= k; i++) {
		ll x0, y0;
		ll c = a[i] - ans;
		ll g = exgcd(M, r[i], x0, y0);
		if (c % g != 0) return -1;
		x0 = (__int128)x0 * (c / g) % (r[i] / g);
		ans = x0 * M + ans;
		M = lcm(M, r[i]);
		ans = (ans % M + M) % M;
	}
	return ans;//无解返回-1
}