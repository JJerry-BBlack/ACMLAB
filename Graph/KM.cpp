//KM算法适用于求解完美匹配下的最大权匹配,时间复杂度O(n^3)
const int INF=0x3f3f3f3f;
const int N=305;
int n,m,match[N],pre[N];
bool vis[N];
int favor[N][N];
int val1[N],val2[N],slack[N];
void bfs(int p)
{
	memset(pre,0,sizeof pre);
	memset(slack,INF,sizeof slack);
	match[0]=p;
	int x=0,nex=0;
	do{
		vis[x]=true;
		int y=match[x],d=INF;
		// 对于当前节点y，bfs有连边的下一点
		for(int i=1;i<=m;i++)
		{
			if(!vis[i])
			{
				if(slack[i]>val1[y]+val2[i]-favor[y][i])
				{
					slack[i]=val1[y]+val2[i]-favor[y][i];
					pre[i]=x;
				}
				if(slack[i]<d)
				{
					d=slack[i];
					nex=i;
				}
			}
		}
		for(int i=0;i<=m;i++)
		{
			if(vis[i])
			val1[match[i]]-=d,val2[i]+=d;
			else
			slack[i]-=d;
		}
		x=nex;
	}while(match[x]);
	
	// pre数组对bfs访问路径进行记录，在最后一并改变match
	while(x)
	{
		match[x]=match[pre[x]];
		x=pre[x];
	}
}
int KM()
{
	memset(match,0,sizeof match);
	memset(val1,0,sizeof val1);
	memset(val2,0,sizeof val2);
	for(int i=1;i<=n;i++)
	{
		memset(vis,false,sizeof vis);
		bfs(i);
	}
	int res=0;
	for(int i=1;i<=m;i++)
	res+=favor[match[i]][i];
	return res;
}
int main()
{
	// Input favor[i][j]
	
	printf("%d",KM());
	
	return 0;
}