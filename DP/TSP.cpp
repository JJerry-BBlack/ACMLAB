#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
int mp[50][50];
struct node
{
	int now,set;
};
long long dp[21][1<<21];
bool vis[21][1<<21];
///设dp状态i,j表示当前在i城市，已经访问的城市集合为j
queue<node>q;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)mp[i][j]=INF;
	
	for(int i=1;i<=n;i++)
	for(int j=0;j<=1<<n;j++)dp[i][j]=INF;
	
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int ta,tb,tc;
		scanf("%d%d%d",&ta,&tb,&tc);
		mp[ta][tb]=min(mp[ta][tb],tc);
		mp[tb][ta]=min(mp[tb][ta],tc);
	}
	dp[1][0]=0;
	vis[1][0]=1;
	q.push({1,0});
	while(!q.empty())
	{
		node p=q.front();
		q.pop();
		int now=p.now,set=p.set;
		vis[now][set]=0;
		for(int i=1;i<=n;i++)
		{
			if((set&(1<<(i-1)))||i==now);
			else
			{
				if(dp[i][set|(1<<(i-1))]>dp[now][set]+mp[now][i])
				{
					dp[i][set|(1<<(i-1))]=dp[now][set]+mp[now][i];
					
					if (vis[i][set|(1<<(i-1))]==0)
					{
						q.push({i,set|(1<<(i-1))});
						vis[i][set|(1<<(i-1))]=1;
					}
				}
			}
		}
	}
	if (n==1)printf("0");
	else printf("%lld\n",dp[1][(1<<n)-1]);
	///dis[i]表示城市1到城市i的最短路距离
	///dis[t]现在还不是最短路，那么肯定存在j,dis[j]+w(j,t)<dis[t]
	///queue<int>q;q.push(i),q.front();
	return 0;
}