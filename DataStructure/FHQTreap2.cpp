//区间翻转
namespace FHQ_Treap
{
	int tot,root;
	int ls[100005],rs[100005],laz[100005];
	int siz[100005],val[100005],rnd[100005];
	#include<random>
	mt19937 rand(233);
	inline int newnode(int w)
	{
		val[++tot]=w;
		rnd[tot]=rand();
		siz[tot]=1;
		return tot;
	}
	inline void pushup(int now)
	{
		siz[now]=siz[ls[now]]+siz[rs[now]]+1;
	}
	inline void pushdown(int now)
	{
		swap(ls[now],rs[now]);
		laz[ls[now]]^=1;
		laz[rs[now]]^=1;
		laz[now]=0;
	}
	void split(int now,int size,int &x,int &y)//按大小分裂
	{
		if(!now)x=y=0;
		else
		{
			if(laz[now])pushdown(now);
			if(siz[ls[now]]<size)
			{
				x=now;
				split(rs[now],size-siz[ls[now]]-1,rs[now],y);
			}
			else
			{
				y=now;
				split(ls[now],size,x,ls[now]);
			}
			pushup(now);
		}
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		if(rnd[x]>rnd[y])
		{
			if(laz[x])pushdown(x);
			rs[x]=merge(rs[x],y);
			pushup(x);
			return x;
		}
		else
		{
			if(laz[y])pushdown(y);
			ls[y]=merge(x,ls[y]);
			pushup(y);
			return y;
		}
	}
	void reverse(int l,int r)
	{
		int x,y,z;
		split(root,l-1,x,y);
		split(y,r-l+1,y,z);
		laz[y]^=1;
		merge(merge(x,y),z);
	}
	void ldr(int now)//中序遍历
	{
		if(!now)return;
		if(laz[now])pushdown(now);
		ldr(ls[now]);
		printf("%d ",val[now]);
		ldr(rs[now]);
	}
}
using namespace FHQ_Treap;

void solve()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	root=merge(root,newnode(i));
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		reverse(l,r);
	}
	ldr(root);
}