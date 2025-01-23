int MAX=1e6+1;
vector<mint>fac,inv,finv;
void binom_init()
{
	fac.resize(MAX);
	finv.resize(MAX);
	inv.resize(MAX);
	fac[0]=fac[1]=1;
	inv[1]=1;
	finv[0]=finv[1]=1;
	for(int i=2;i<MAX;i++)
	{
		fac[i]=fac[i-1]*i;
		inv[i]=-(MOD/i)*inv[MOD%i];
		finv[i]=finv[i-1]*inv[i];
	}
}
mint binom(int n,int r)
{
	if(n<r||n<0||r<0)return 0;
	return fac[n]*finv[r]*finv[n-r];
}