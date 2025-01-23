namespace Kruskal_Rebuild_Tree
{
	struct EDGE
	{
		int a,b,c;
		bool operator<(const EDGE& e)const{return c<e.c;}
	};
	vector<EDGE>e(m+1);
	vector<int>edge[n+m+1];
	int st[n+m+1],fa[n+m+1],dep[n+m+1];
	int f[n+m+1][20];
	int findd(int a)
	{
		return fa[a]==a?a:fa[a]=findd(fa[a]);
	};
	void kruskal()
	{
		sort(e.begin()+1,e.end());
		for(int i=1;i<=m;i++)
		{
			int u=findd(e[i].a),v=findd(e[i].b),w=e[i].c;
			if(u!=v)
			{
				st[++n]=w;
				fa[n]=fa[u]=fa[v]=n;
				edge[n].push_back(u);
				edge[n].push_back(v);
				edge[u].push_back(n);
				edge[v].push_back(n);
			}
		}
	}
	void lca_init(int u,int father)
	{
		f[u][0]=father;dep[u]=dep[father]+1;
		for(int i=1;i<20;i++)f[u][i]=f[f[u][i-1]][i-1];
		for(auto v:edge[u])
		{
			if(v==father)continue;
			lca_init(v,u);
		}
	}
	int cal_lca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i=19;i>=0;i--)if(dep[f[x][i]]>=dep[y])x=f[x][i];
		if(x==y)return x;
		for(int i=19;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
		return f[x][0];
	}
}
using namespace Kurskal_Rebuild_Tree;
void solve()
{
	int n,m,q;
	read(n,m,q);
	for(int i=1;i<=m;i++)read(e[i].a,e[i].b,e[i].c);
	for(int i=1;i<=n;i++)fa[i]=i;
	
	kruskal();
	lca_init(n,0);
	for(int i=1;i<=q;i++)
	{
		int u,v,w;
		read(u,v,w);
		int lca=cal_lca(u,v);
		if(st[lca]>w)println("Yes");
		else println("No");
	}
}