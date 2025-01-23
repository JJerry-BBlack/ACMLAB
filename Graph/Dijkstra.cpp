struct Edge
{
	int to,dis;
};
vector<Edge>edge[200005];
struct city
{
	int id,dis;
	bool operator<(const city& c)const
	{
		return dis>c.dis;
	}
};
priority_queue<city>q;
int dis[200005];
int vis[200005];
int n,m;
int s,t;
void init()
{
	for(int i=1;i<=n;i++)
	{
		dis[i]=INF;
		vis[i]=0;
	}
	dis[s]=0;
	q.push({s,0});
}
void dijkstra()
{
	while(!q.empty())
	{
		auto [id,d]=q.top();
		q.pop();
		if(vis[id])continue;
		else vis[id]=1;
		for(auto [it,dd]:edge[id])
		{
			if(dis[it]>dis[id]+dd)
			{
				dis[it]=dis[id]+dd;
				q.push({it,dis[it]});
			}
		}
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=0;i<n;i++)edge[i].clear();
		while(!q.empty())q.pop();
		for(int i=1;i<=m;i++)
		{
			int from,to,d;
			scanf("%d%d%d",&from,&to,&d);
			edge[from].push_back({to,d});
			edge[to].push_back({from,d});
		}
		scanf("%d%d",&s,&t);
		init();
		dijkstra();
		if(dis[t]==1e9)printf("-1\n");
		else printf("%d\n",dis[t]);
	}
	return 0;
}