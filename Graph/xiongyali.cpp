const int MAXN=505;
int k,n,m;
int Map[MAXN][MAXN];
int p[MAXN];
bool vis[MAXN];
bool match(int i)
{
	for (int j=1;j<=m;j++)
	{
		if(Map[i][j]&&!vis[j])
		{
			vis[j]=1;
			if(p[j]==0||match(p[j]))
			{
				p[j]=i;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d",&k) != EOF)
	{
		memset(Map,0,sizeof(Map));
		memset(p,0,sizeof(p));
		if(k==0)return 0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=k;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			Map[x][y]=1;
		}
		int cnt=0;
		for (int i=1;i<=n;i++)
		{
			memset(vis,0,sizeof(vis));
			if(match(i))cnt++;
		}
		printf("%d\n",cnt);
	}
	return 0;
}