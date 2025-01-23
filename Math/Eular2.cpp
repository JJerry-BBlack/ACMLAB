const int maxn=10000000;
bool not_prime[maxn+5];
int prime[maxn+5],tot=0,phi[maxn+5];
for(int i=2;i<=n;i++)
{
	if(!not_prime[i])prime[++tot]=i,phi[i]=i-1;
	for(int j=1;j<=tot&&i*prime[j]<=n;j++)
	{
		not_prime[i*prime[j]]=1;
		if(i%prime[j]==0)
		{
			phi[i*prime[j]]=phi[i]*prime[j];
			break;
		}
		phi[i*prime[j]]=phi[i]*(prime[j]-1);
	}
}