#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int type,u,v;
};
vector<int>adj[200005];
int col[200005],topo[200005];
void dfs(int v)
{
	for(int u:adj[v])if(col[u]==-1)
	{
		col[u]=col[v]^1;
		dfs(u);
	}
}
bool BipartiteColoring(int n)
{
	for(int i=1;i<=n;i++)col[i]=-1;
	for(int i=1;i<=n;i++)if(col[i]==-1)
	{
		col[i]=0;
		dfs(i);
	}
	for(int i=1;i<=n;i++)for(int j:adj[i])if(col[i]==col[j])return 0;
	return 1;
}
bool TopologicalSort(int n)
{
	vector<int>in(n+1,0);
	for(int i=1;i<=n;i++)for(int j:adj[i])in[j]++;
	queue<int>q;
	for(int i=1;i<=n;i++)if(in[i]==0)q.push(i);
	int ord=0;
	while(!q.empty())
	{
		int v=q.front();
		q.pop();
		topo[v]=ord++;
		for(int u:adj[v])
		{
			in[u]--;
			if(in[u]==0)q.push(u);
		}
	}
	return ord==n;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	vector<edge>a(m);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&a[i].type,&a[i].u,&a[i].v);
		adj[a[i].u].push_back(a[i].v);
		adj[a[i].v].push_back(a[i].u);
	}
	if(!BipartiteColoring(n)){printf("NO\n");return 0;}
	// col = 0 -> orient left, col = 1 -> orient right
	for(int i=1;i<=n;i++)adj[i].clear();
	for(edge e:a)
	{
		if(col[e.u]==1)swap(e.u,e.v);
		if(e.type==1)adj[e.u].push_back(e.v);
		else adj[e.v].push_back(e.u);
	}
	if(!TopologicalSort(n)){printf("NO\n");return 0;}
	printf("YES\n");
	for(int i=1;i<=n;i++)
	{
		col[i]==1?printf("R %d\n",topo[i]):printf("L %d\n",topo[i]);
	}
	return 0;
}