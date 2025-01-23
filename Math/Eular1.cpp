long long get_phi(long long n)
{
	long long phi=1;
	for(int i=2;i<=n/i;i++)
	{
		if(n%i==0)
		{
			phi*=(i-1);
			n/=i;
			while(n%i==0)phi*=i,n/=i;
		}
	}
	if(n>1)phi*=(n-1);
	return phi;
}