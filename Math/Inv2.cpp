const int maxn=10000000;
long long inv[maxn+5];
inv[1]=1;
for(int i=2;i<=maxn;i++)
{
	inv[i]=inv[p%i]*(p-p/i)%p;
}