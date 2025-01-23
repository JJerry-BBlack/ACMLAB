inline ll mull(const ll&a,const ll&b,const ll&mod)
{
	ll tmp=a*b-(ll)((long double)a/mod*b-1e-9)*mod;
	return tmp<0?tmp+mod:tmp;
}