#include<bits/stdc++.h>
using namespace std;
namespace Segtree
{
	int n,m;
	int a[500005];
	struct node
	{
		int sum,max_l,max_r,maxx;
		node operator+(const node& y)const
		{
			return {sum+y.sum,
				max(max_l,sum+y.max_l),
				max(max_r+y.sum,y.max_r),
				max({maxx,y.maxx,max_r+y.max_l})};
		}
	}tree[500005<<2];
	void build(int p,int l,int r)
	{
		if(l==r)tree[p]={a[l],a[l],a[l],a[l]};
		else
		{
			int mid=(l+r)>>1;
			build(p<<1,l,mid);
			build(p<<1|1,mid+1,r);
			tree[p]=tree[p<<1]+tree[p<<1|1];
		}
	}
	void update(int p,int l,int r,int w,int x)
	{
		if(l==r)tree[p]={w,w,w,w};
		else
		{
			int mid=(l+r)>>1;
			if(x<=mid)update(p<<1,l,mid,w,x);
			else update(p<<1|1,mid+1,r,w,x);
			tree[p]=tree[p<<1]+tree[p<<1|1];
		}
	}
	node query(int p,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return tree[p];
		else
		{
			node ans={0,(int)-1e9,(int)-1e9,(int)-1e9};
			int mid=(l+r)>>1;
			if(x<=mid)ans=ans+query(p<<1,l,mid,x,y);
			if(mid<y)ans=ans+query(p<<1|1,mid+1,r,x,y);
			return ans;
		}
	}
}
using namespace Segtree;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	build(1,1,n);
	while(m--)
	{
		int op,l,r;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1)
		{
			if(l>r)swap(l,r);
			printf("%d\n",query(1,1,n,l,r).maxx);
		}
		else update(1,1,n,r,l);
	}
	return 0;
}