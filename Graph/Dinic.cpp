const int MAXN=1000005;
const int inf=1000000000;
int S,T;
struct EDGE
{
	int v,flow,nxt;
}edge[MAXN<<2];
int head[MAXN],cur[MAXN],num=0;
int dep[MAXN],q[MAXN];
void add_edge(int u,int v,int w)
{
	edge[num].v=v;
	edge[num].flow=w;
	edge[num].nxt=head[u];
	head[u]=num++;
}
void Add_edge(int u,int v,int w)
{
	add_edge(u,v,w);
	add_edge(v,u,0);
}
bool bfs()
{
	memset(dep,0,sizeof(dep));
	dep[S]=1;
	int l=0,r=1;
	q[++l]=S;
	while(l<=r)
	{
		int p=q[l++];
		if(p==T)break;
		for(int i=head[p];~i;i=edge[i].nxt)
		{
			if(!dep[edge[i].v]&&edge[i].flow)
			{
				dep[edge[i].v]=dep[p]+1;
				q[++r]=edge[i].v;
				if(edge[i].v==T)return 1;
			}
		}
	}
	return dep[T];
}
int dfs(int now,int nowflow)
{
	if(now==T)return nowflow;
	int totflow=0;
	for(int& i=cur[now];~i;i=edge[i].nxt)
	{
		if(dep[edge[i].v]==dep[now]+1&&edge[i].flow)
		{
			int canflow=dfs(edge[i].v,min(nowflow,edge[i].flow));
			edge[i].flow-=canflow;
			edge[i^1].flow+=canflow;
			totflow+=canflow;
			nowflow-=canflow;
			if(nowflow<=0)break;
		}
	}
	return totflow;
}
int dinic()
{
	int ans=0;
	while(bfs())
	{
		memcpy(cur,head,sizeof(head));
		ans+=dfs(S,inf);
	}
	return ans;
}
void init()
{
	memset(q,0,sizeof(q));
	memset(cur,0,sizeof(cur));
	memset(dep,0,sizeof(dep));
	memset(head,-1,sizeof(head));
	for(int i=0;i<=num;i++)edge[i].v=edge[i].flow=edge[i].nxt=0;
	num=0;
}