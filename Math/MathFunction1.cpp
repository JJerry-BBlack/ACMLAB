ll get_f(ll n)
{
	ll ans=1;
	for(int i=2;i<=n/i;i++)
	{
		int cnt=0;
		while(n%i==0)cnt++,n/=i;
		ans*=calc_f(i,cnt);//calc_f(p,k)=f[p^k]
	}
	if(n>1)ans*=calc_f(n,1);
	return ans;
}