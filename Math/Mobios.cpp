int prime[10000005];
int vis[10000005];
int mo[10000005];
int len=0;
void init()
{
	mo[1]=1;
	for(int i=2;i<=10000000;i++)
	{
		if(!vis[i])
		{
			prime[++len]=i;
			mo[i]=-1;
		}
		for(int j=1;;j++)
		{
			long long t=1ll*prime[j]*i;
			if(t>10000000)break;
			vis[t]=1;
			if(i%prime[j]==0){mo[t]=0;break;}
			else mo[t]=-mo[i];
		}
	}
}