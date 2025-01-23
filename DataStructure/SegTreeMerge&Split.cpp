// 给出一个可重集 a（编号为 1），它支持以下操作：
// 0 p x y：将可重集 p 中大于等于 x 且小于等于 y 的值移动到一个新的可重集中（新可重集编号为从 2 开始的正整数，是上一次产生的新可重集的编号+1）。
// 1 p t：将可重集 t 中的数放入可重集 p，且清空可重集 t（数据保证在此后的操作中不会出现可重集 t）。
// 2 p x q：在 p 这个可重集中加入 x 个数字 q。
// 3 p x y：查询可重集 p 中大于等于 x 且小于等于 y 的值的个数。
// 4 p k：查询在 p 这个可重集中第 k 小的数，不存在时输出 -1。

namespace Segtree
{
	int n,m;
	int ls[(n+1)*40],rs[(n+1)*40],root[n+1];
	ll tree[(n+1)*40];
	int cnt=0,top=1;
	void update(int& p,int l,int r,ll w,int x)
	{
		if(!p)p=++cnt;
		if(l==r)tree[p]+=w;
		else
		{
			int mid=(l+r)>>1;
			if(x<=mid)update(ls[p],l,mid,w,x);
			else update(rs[p],mid+1,r,w,x);
			tree[p]=tree[ls[p]]+tree[rs[p]];
		}
	}
	int merge(int a,int b,int l,int r)
	{
		if(!a||!b)return a+b;
		else if(l==r)
		{
			tree[a]+=tree[b];
			return a;
		}
		else
		{
			int mid=(l+r)>>1;
			ls[a]=merge(ls[a],ls[b],l,mid);
			rs[a]=merge(rs[a],rs[b],mid+1,r);
			tree[a]=tree[ls[a]]+tree[rs[a]];
			return a;
		}
	}
	void split(int& p,int& q,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)
		{
			p=q;
			q=0;
		}
		else
		{
			if(!p)p=++cnt;
			int mid=(l+r)>>1;
			if(x<=mid)split(ls[p],ls[q],l,mid,x,y);
			if(mid<y)split(rs[p],rs[q],mid+1,r,x,y);
			tree[p]=tree[ls[p]]+tree[rs[p]];
			tree[q]=tree[ls[q]]+tree[rs[q]];
		}
	}
	ll query1(int p,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return tree[p];
		else
		{
			int mid=(l+r)>>1;
			ll ans=0;
			if(x<=mid)ans+=query1(ls[p],l,mid,x,y);
			if(mid<y)ans+=query1(rs[p],mid+1,r,x,y);
			return ans;
		}
	}
	int query2(int p,int l,int r,ll x)
	{
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(tree[ls[p]]>=x)return query2(ls[p],l,mid,x);
		else if(tree[rs[p]]>=x-tree[ls[p]])return query2(rs[p],mid+1,r,x-tree[ls[p]]);
		else return -1;
	}
}
using namespace Segtree;
void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		update(root[top],1,n,x,i);
	}
	for(int i=1;i<=m;i++)
	{
		int op;
		scanf("%d",&op);
		if(op==0)
		{
			int p,x,y;
			scanf("%d%d%d",&p,&x,&y);
			split(root[++top],root[p],1,n,x,y);
		}
		else if(op==1)
		{
			int p,t;
			scanf("%d%d",&p,&t);
			root[p]=merge(root[p],root[t],1,n);
			root[t]=0;
		}
		else if(op==2)
		{
			int p,x,q;
			scanf("%d%d%d",&p,&x,&q);
			update(root[p],1,n,x,q);
		}
		else if(op==3)
		{
			int p,x,y;
			scanf("%d%d%d",&p,&x,&y);
			printf("%lld\n",query1(root[p],1,n,x,y));
		}
		else if(op==4)
		{
			int p,k;
			scanf("%d%d",&p,&k);
			printf("%d\n",query2(root[p],1,n,k));
		}
		//		printf("query%d:\n",i);
		//		for(int j=1;j<=top;j++)
		//		{
			//			printf("%d:",j);
			//			for(int k=1;k<=n;k++)printf("%d%c",query1(root[j],1,n,k,k)," \n"[k==n]);
			//		}
	}
}