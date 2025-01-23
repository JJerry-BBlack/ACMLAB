const int maxn=10000000;
bool not_prime[maxn+5];
int prime[maxn+5],tot=0;
for(int i=2;i<=maxn;i++)
{
	if(!not_prime[i])prime[++tot]=i;
	for(int j=1;j<=tot&&i*prime[j]<=maxn;j++)
	{
		not_prime[i*prime[j]]=1;
		if(i%prime[j]==0)break;
	}
}