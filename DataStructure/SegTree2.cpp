#include<bits/stdc++.h>
using namespace std;
long long mod;
namespace Segtree
{
	int a[100005];
	long long tree[100005<<2],laz1[100005<<2],laz2[100005<<2];
	void build(int p,int l,int r)
	{
		laz1[p]=0,laz2[p]=1;
		if(l==r)tree[p]=a[l]%mod;
		else
		{
			int mid=(l+r)>>1;
			build(p<<1,l,mid);
			build(p<<1|1,mid+1,r);
			tree[p]=(tree[p<<1]+tree[p<<1|1])%mod;
		}
	}
	void pushdown(int p,int l,int r)
	{
		int mid=(l+r)>>1;
		long long x=laz1[p],y=laz2[p];
		tree[p<<1]=(tree[p<<1]*y%mod+x*(mid-l+1)%mod)%mod;
		tree[p<<1|1]=(tree[p<<1|1]*y%mod+x*(r-mid)%mod)%mod;
		laz1[p<<1]=(laz1[p<<1]*y%mod+x)%mod;
		laz1[p<<1|1]=(laz1[p<<1|1]*y%mod+x)%mod;
		laz2[p<<1]=laz2[p<<1]*y%mod;
		laz2[p<<1|1]=laz2[p<<1|1]*y%mod;
		laz1[p]=0,laz2[p]=1;
	}
	void update(int p,int l,int r,long long w,int x,int y,int op)
	{
		if(op==2)//加
		{
			if(x<=l&&r<=y)
			{
				tree[p]=(tree[p]+w*(r-l+1)%mod)%mod;
				laz1[p]=(laz1[p]+w)%mod;
			}
			else
			{
				pushdown(p,l,r);
				int mid=(l+r)>>1;
				if(x<=mid)update(p<<1,l,mid,w,x,y,op);
				if(mid<y)update(p<<1|1,mid+1,r,w,x,y,op);
				tree[p]=(tree[p<<1]+tree[p<<1|1])%mod;
			}
		}
		else//乘
		{
			if(x<=l&&r<=y)
			{
				tree[p]=tree[p]*w%mod;
				laz1[p]=laz1[p]*w%mod;
				laz2[p]=laz2[p]*w%mod;
			}
			else
			{
				pushdown(p,l,r);
				int mid=(l+r)>>1;
				if(x<=mid)update(p<<1,l,mid,w,x,y,op);
				if(mid<y)update(p<<1|1,mid+1,r,w,x,y,op);
				tree[p]=(tree[p<<1]+tree[p<<1|1])%mod;
			}
		}
	}
	long long query(int p,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return tree[p]%mod;
		else
		{
			pushdown(p,l,r);
			long long ans=0;
			int mid=(l+r)>>1;
			if(x<=mid)ans=(ans+query(p<<1,l,mid,x,y))%mod;
			if(mid<y)ans=(ans+query(p<<1|1,mid+1,r,x,y))%mod;
			tree[p]=(tree[p<<1]+tree[p<<1|1])%mod;
			return ans;
		}
	}
}
using namespace Segtree;
int main()
{
	int n,m;
	scanf("%d%d%lld",&n,&m,&mod);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,1,n);
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1||op==2)
		{
			int l,r;long long w;
			scanf("%d%d%lld",&l,&r,&w);
			update(1,1,n,w,l,r,op);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,1,n,l,r));
		}
	}
	return 0;
}