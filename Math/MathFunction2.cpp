f[1]=1;
for(int i=2;i<=n;i++)
{
	if(!isprime[i])prime[++tot]=i,f[i]=calc_f(i,1);
	for(int j=1;j<=tot&&i*prime[j]<=n;j++)
	{
		if(i%p[j]==0)
		{
			cnt[i*p[j]]=cnt[i]+1;//cnt[n]:n的最小质因子的次数
			f[i*p[j]]=f[i]/calc_f(p[j],cnt[i])*calc_f(p[j],cnt[i]+1);
			break;
		}
		cnt[i*p[j]]=1;
		f[i*p[j]]=f[i]*calc_f(p[j],1);
	}
}