struct Query
{
	int s,lca,l,r,id,pos;
	bool operator<(const Query &x)const
	{
		return (pos^x.pos)?pos<x.pos:(pos&1)?r<x.r:r>x.r;
	}
}a[100005];
int b[40005],d[40005],cntd,n,m;
int cnt[40005],vis[40005],Ans[100005];
vector<int>edge[40005];
int fa[40005][20],dep[40005];
int c[80005],tot,fir[40005],las[40005];
void dfs(int x,int father)
{
	fa[x][0]=father;dep[x]=dep[father]+1;
	for(int i=1;i<20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	c[++tot]=x;fir[x]=tot;
	for(auto it:edge[x])if(it!=father)dfs(it,x);
	c[++tot]=x;las[x]=tot;
}
int cal_lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void solve()
{
	read(n,m);
	int siz=(int)sqrt(2*n);
	for(int i=1;i<=n;i++)
	{
		read(b[i]);
		d[++cntd]=b[i];
	}
	sort(d+1,d+cntd+1);
	cntd=unique(d+1,d+cntd+1)-d-1;
	for(int i=1;i<=n;i++)
	b[i]=lower_bound(d+1,d+cntd+1,b[i])-d;
	for(int i=1;i<n;i++)
	{
		int x,y;read(x,y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(1,1);
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x,y);
		if(fir[x]>fir[y])swap(x,y);a[i].s=x;
		((a[i].lca=cal_lca(x,y))==x)?a[i].l=fir[x]:a[i].l=las[x];
		a[i].r=fir[y];a[i].pos=(a[i].l-1)/siz+1;a[i].id=i;
	}
	sort(a+1,a+m+1);
	int l=1,r=0,ans=0;
	for(int i=1;i<=m;i++)
	{
		while(l>a[i].l)(vis[c[--l]]?ans-=!--cnt[b[c[l]]]:
		ans+=!cnt[b[c[l]]]++),vis[c[l]]^=1;
		while(l<a[i].l)(vis[c[l]]?ans-=!--cnt[b[c[l]]]:
		ans+=!cnt[b[c[l]]]++),vis[c[l++]]^=1;
		while(r<a[i].r)(vis[c[++r]]?ans-=!--cnt[b[c[r]]]:
		ans+=!cnt[b[c[r]]]++),vis[c[r]]^=1;
		while(r>a[i].r)(vis[c[r]]?ans-=!--cnt[b[c[r]]]:
		ans+=!cnt[b[c[r]]]++),vis[c[r--]]^=1;
		Ans[a[i].id]=((a[i].lca==a[i].s)?ans:ans+
		(vis[a[i].lca]?((cnt[b[a[i].lca]]==1)?-1:0):((cnt[b[a[i].lca]]==0)?1:0)));
	}
	for(int i=1;i<=m;i++)println(Ans[i]);
}