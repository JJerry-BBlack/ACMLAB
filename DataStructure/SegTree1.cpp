#include<bits/stdc++.h>
using namespace std;
namespace Segtree
{
	int n,m;
	double tree[1005<<2],laz1[1005<<2],laz2[1005<<2];
	void pushdown(int p,int l,int r)
	{
		int mid=(l+r)>>1;
		double x=laz1[p],y=laz2[p];
		laz1[p<<1]+=x;
		laz2[p<<1]+=y;
		laz1[p<<1|1]+=x+y*(mid-l+1);
		laz2[p<<1|1]+=y;
		tree[p<<1]+=(x+x+(mid-l)*y)*(mid-l+1)/2;
		tree[p<<1|1]+=(x+y*(mid-l+1)+x+y*(mid-l+1)+(r-mid-1)*y)*(r-mid)/2;
		laz1[p]=laz2[p]=0;
	}
	void build(int p,int l,int r)
	{
		laz1[p]=laz2[p]=0;
		if(l==r)tree[p]=n-1;
		else
		{
			int mid=(l+r)>>1;
			build(p<<1,l,mid);
			build(p<<1|1,mid+1,r);
			tree[p]=tree[p<<1]+tree[p<<1|1];
		}
	}
	void update(int p,int l,int r,double v,double d,int x,int y)
	{
		if(x<=l&&r<=y)
		{
			double vv=v+(l-x)*d;
			laz1[p]+=vv;
			laz2[p]+=d;
			tree[p]+=(vv+vv+d*(r-l))*(r-l+1)/2;
		}
		else
		{
			int mid=(l+r)>>1;
			pushdown(p,l,r);
			if(x<=mid)update(p<<1,l,mid,v,d,x,y);
			if(mid<y)update(p<<1|1,mid+1,r,v,d,x,y);
			tree[p]=tree[p<<1]+tree[p<<1|1];
		}
	}
	double query(int p,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return tree[p];
		else
		{
			pushdown(p,l,r);
			int mid=(l+r)>>1;
			double ans=0;
			if(x<=mid)ans+=query(p<<1,l,mid,x,y);
			if(mid<y)ans+=query(p<<1|1,mid+1,r,x,y);
			tree[p]=tree[p<<1]+tree[p<<1|1];
			return ans;
		}
	}
	int h[100005];
}
using namespace Segtree;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&h[i]);
	build(1,1,1000);
	for(int i=0;i<n-1;i++)
	{
		int minn=min(h[i],h[i+1]);
		int maxx=max(h[i],h[i+1]);
		if(minn>=1)update(1,1,1000,-1,0,1,minn);
		if(maxx>minn)update(1,1,1000,-(1.0-1.0/(maxx-minn)/2),1.0/(maxx-minn),minn+1,maxx);
	}
	while(m--)
	{
		char op[10];
		scanf("%s",op+1);
		if(op[1]=='Q')
		{
			int H;
			scanf("%d",&H);
			if(H==0)printf("0.000\n");
			else printf("%.3f\n",query(1,1,1000,1,H));
		}
		else
		{
			int id,H;
			scanf("%d%d",&id,&H);
			if(id>0)
			{
				if(h[id]>h[id-1])
				{
					update(1,1,1000,1.0-1.0/(h[id]-h[id-1])/2,-1.0/(h[id]-h[id-1]),h[id-1]+1,h[id]);
				}
				else if(h[id]<h[id-1])
				{
					update(1,1,1000,-1.0/(h[id-1]-h[id])/2,-1.0/(h[id-1]-h[id]),h[id]+1,h[id-1]);
				}
				if(H>h[id-1])
				{
					update(1,1,1000,-(1.0-1.0/(H-h[id-1])/2),1.0/(H-h[id-1]),h[id-1]+1,H);
				}
				else if(H<h[id-1])
				{
					update(1,1,1000,1.0/(h[id-1]-H)/2,1.0/(h[id-1]-H),H+1,h[id-1]);
				}
			}
			if(id<n-1)
			{
				if(h[id]>h[id+1])
				{
					update(1,1,1000,1.0-1.0/(h[id]-h[id+1])/2,-1.0/(h[id]-h[id+1]),h[id+1]+1,h[id]);
				}
				else if(h[id]<h[id+1])
				{
					update(1,1,1000,-1.0/(h[id+1]-h[id])/2,-1.0/(h[id+1]-h[id]),h[id]+1,h[id+1]);
				}
				if(H>h[id+1])
				{
					update(1,1,1000,-(1.0-1.0/(H-h[id+1])/2),1.0/(H-h[id+1]),h[id+1]+1,H);
				}
				else if(H<h[id+1])
				{
					update(1,1,1000,1.0/(h[id+1]-H)/2,1.0/(h[id+1]-H),H+1,h[id+1]);
				}
			}
			h[id]=H;
		}
	}
	return 0;
}