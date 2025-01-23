//普通版本
namespace FHQ_Treap
{
	int tot,root;
	int ls[100005],rs[100005];
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
	void split(int now,int w,int &x,int &y)//按值分裂
	{
		if(!now)x=y=0;
		else
		{
			if(val[now]<=w)
			{
				x=now;
				split(rs[now],w,rs[now],y);
			}
			else
			{
				y=now;
				split(ls[now],w,x,ls[now]);
			}
			pushup(now);
		}
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		if(rnd[x]>rnd[y])//>、>=、<、<=都可以
		{
			rs[x]=merge(rs[x],y);
			pushup(x);
			return x;
		}
		else
		{
			ls[y]=merge(x,ls[y]);
			pushup(y);
			return y;
		}
	}
	int x,y,z;
	inline void insert(int w)
	{
		split(root,w,x,y);
		root=merge(merge(x,newnode(w)),y);
	}
	inline void del(int w)
	{
		split(root,w,x,z);
		split(x,w-1,x,y);
		y=merge(ls[y],rs[y]);
		root=merge(merge(x,y),z);
	}
	inline int queryrnk(int w)
	{
		split(root,w-1,x,y);
		int ans=siz[x]+1;
		root=merge(x,y);
		return ans;
	}
	inline int querynum(int rnk)
	{
		int now=root;
		while(now)
		{
			if(siz[ls[now]]+1==rnk)break;
			else if(siz[ls[now]]>=rnk)now=ls[now];
			else
			{
				rnk-=siz[ls[now]]+1;
				now=rs[now];
			}
		}
		return val[now];
	}
	inline int pre(int w)
	{
		split(root,w-1,x,y);
		int now=x;
		while(rs[now])now=rs[now];
		root=merge(x,y);
		return val[now];
	}
	inline int sub(int w)
	{
		split(root,w,x,y);
		int now=y;
		while(ls[now])now=ls[now];
		root=merge(x,y);
		return val[now];
	}
}
using namespace FHQ_Treap;

void solve()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int op,w;
		scanf("%d%d",&op,&w);
		if(op==1)insert(w);
		else if(op==2)del(w);
		else if(op==3)printf("%d\n",queryrnk(w));
		else if(op==4)printf("%d\n",querynum(w));
		else if(op==5)printf("%d\n",pre(w));
		else printf("%d\n",sub(w));
	}
}