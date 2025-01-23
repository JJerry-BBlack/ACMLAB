#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
const int sqN=1005;

int n,sq;
int st[sqN];//第i号块的第一个元素的下标
int ed[sqN];//第i号块最后一个元素的下标
int id[N];//元素i的分块编号

ll arr[N];//零散数组
ll sum[N];//分块和数组
ll laz[N];//分块公共加数组

void init()
{
	sq=(int)sqrt(n);
	for(int i=1;i<=sq;i++)
	{
		st[i]=n/sq*(i-1)+1;
		ed[i]=n/sq*i;
	}
	ed[sq]=n;
	
	for(int i=1;i<=sq;i++)
	{
		for(int j=st[i];j<=ed[i];j++)
		{
			id[j]=i;
			sum[i]+=arr[j];
		}
	}
}

void update(int l,int r,ll x)
{
	if(id[l]==id[r])
	{
		for(int i=l;i<=r;i++)arr[i]+=x;
		sum[id[l]]+=x*(r-l+1);
	}
	else
	{
		for(int i=l;i<=ed[id[l]];i++)arr[i]+=x;
		sum[id[l]]+=x*(ed[id[l]]-l+1);
		for(int i=st[id[r]];i<=r;i++)arr[i]+=x;
		sum[id[r]]+=x*(r-st[id[r]]+1);
		for(int i=id[l]+1;i<id[r];i++)laz[i]+=x;
	}
}

ll query(int l,int r)
{
	ll ans=0;
	if(id[l]==id[r])
	{
		for(int i=l;i<=r;i++)ans+=arr[i];
		ans+=laz[id[l]]*(r-l+1);
	}
	else
	{
		for(int i=l;i<=ed[id[l]];i++)ans+=arr[i];
		ans+=laz[id[l]]*(ed[id[l]]-l+1);
		for(int i=st[id[r]];i<=r;i++)ans+=arr[i];
		ans+=laz[id[r]]*(r-st[id[r]]+1);
		for(int i=id[l]+1;i<id[r];i++)
		ans+=sum[i]+laz[i]*(ed[i]-st[i]+1);
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&arr[i]);
	init();
	for(int i=1;i<=n;i++)
	{
		int op;
		scanf("%d",&op);
		if(op==0)
		{
			int l,r,c;
			scanf("%d%d%d",&l,&r,&c);
			update(l,r,c);
		}
		else
		{
			int l,r,c;
			scanf("%d%d%d",&l,&r,&c);
			printf("%lld\n",query(l,r)%(c+1));
		}
	}
	return 0;
}