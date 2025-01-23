#include<bits/stdc++.h>
using namespace std;
int n,q;
long long a[100005];
vector<int>edge[100005];
int dep[100005],siz[100005],son[100005],fa[100005];
int id[100005],top[100005],tot=0;
void dfs(int x,int father)
{
	siz[x]=1;
	dep[x]=dep[father]+1;
	int maxsize=0;
	for(auto it:edge[x])if(it!=father)
	{
		fa[it]=x;
		dfs(it,x);
		siz[x]+=siz[it];
		if(siz[it]>maxsize)
		{
			maxsize=siz[it];
			son[x]=it;
		}
	}
}
long long k[100005];
void dfs1(int x,int father)
{
	id[x]=++tot;
	k[id[x]]=a[x];
	if(son[x])
	{
		top[son[x]]=top[x];
		dfs1(son[x],x);
	}
	for(auto it:edge[x])if(it!=father&&it!=son[x])
	{
		top[it]=it;
		dfs1(it,x);
	}
}
long long tree[100005<<2];
void build(int p,int l,int r)
{
	if(l==r)
	{
		tree[p]=k[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tree[p]=tree[p<<1]^tree[p<<1|1];
}
void update(int p,int l,int r,long long w,int x)
{
	if(l==r)
	{
		tree[p]=w;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,w,x);
	else update(p<<1|1,mid+1,r,w,x);
	tree[p]=tree[p<<1]^tree[p<<1|1];
}
long long query(int p,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)return tree[p];
	long long ans=0;
	int mid=(l+r)>>1;
	if(x<=mid)ans^=query(p<<1,l,mid,x,y);
	if(mid<y)ans^=query(p<<1|1,mid+1,r,x,y);
	return ans;
}
long long Query(int x,int y)
{
	long long ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans^=query(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	ans^=query(1,1,n,id[y],id[x]);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dep[1]=1;
	dfs(1,0);
	top[1]=1;
	dfs1(1,0);
	build(1,1,n);
	while(q--)
	{
		long long op,l,r;
		scanf("%lld%lld%lld",&op,&l,&r);
		if(op==1)
		{
			update(1,1,n,r,id[l]);
		}
		else
		{
			printf("%lld\n",Query(l,r));
		}
	}
	return 0;
}