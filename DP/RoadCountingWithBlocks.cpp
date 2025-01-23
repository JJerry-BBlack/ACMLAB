//复杂度为O(m^2),m为障碍的个数,此代码包含m个障碍和n个终点,每个终点互不影响
void solve()
{
	binom_init();
	int n,m;
	cin>>n>>m;
	vector<int>x(m+n+1),y(m+n+1),vis(m+n+1);
	vector<Z>dp(m+n+1);
	for(int i=1;i<=m;i++)cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)x[m+i]=i,y[m+i]=n-i+1;
	function<Z(int)>dfs=[&](int i)->Z
	{
		if(vis[i])return dp[i];
		vis[i]=1;
		Z res=0;
		for(int j=1;j<=m;j++)
		{
			if(j!=i&&x[j]<=x[i]&&y[j]<=y[i])
			{
				res+=dfs(j)*binom(x[i]-x[j]+y[i]-y[j],x[i]-x[j]);
			}
		}
		return dp[i]=binom(x[i]-1+y[i]-1,x[i]-1)-res;
	};
	Z ans=0;
	for(int i=m+1;i<=n+m;i++)
	{
		ans+=dfs(i);
	}
	cout<<ans;
}