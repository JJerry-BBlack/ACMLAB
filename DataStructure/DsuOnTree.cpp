#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
vector<int>edge[100005];
int siz[100005],son[100005],rev[100005],dfn[100005],num;
void dfs(int u,int fa)
{
	siz[u]=1;rev[dfn[u]=++num]=u;
	for(int v:edge[u])if(v!=fa)
	{
		dfs(v,u);siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
long long ans[100005],res;
int cnt[100005],maxx;
inline void ins(int x)
{
	cnt[x]++;
	if(maxx<cnt[x])maxx=cnt[x],res=0;
	if(maxx==cnt[x])res+=x;
}
void dsu(int u,int fa,bool kp)
{
	for(int v:edge[u])if(v!=fa&&v!=son[u])dsu(v,u,0);
	if(son[u])dsu(son[u],u,1);
	ins(a[u]);
	for(auto v:edge[u])if(v!=fa&&v!=son[u])
	for(int j=dfn[v];j<=dfn[v]+siz[v]-1;j++)
	ins(a[rev[j]]);
	ans[u]=res;
	if(!kp)
	{
		maxx=res=0;
		for(int i=dfn[u];i<=dfn[u]+siz[u]-1;i++)
		cnt[a[rev[i]]]=0;
	}
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;
		read(x);read(y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(1,0);
	dsu(1,0,1);
	for(int i=1;i<=n;i++){print(ans[i]);putchar(' ');}
	return 0;
}