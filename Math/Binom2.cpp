ll binom(ll n,ll m)
{
	if(n<m||n<0||m<0)return 0;
	if(m>n-m)m=n-m;
	ll ans=1;
	for(int i=0;i<m;i++)
	ans=ans*(n-i)/(i+1); // 取模时记得先单独把 (n-i) 取模
	return ans;
}