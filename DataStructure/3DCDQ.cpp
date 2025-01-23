//求p[i].x<=p[j].x&&p[i].y<=p[j].y&&p[i].z<=p[j].z&&i!=j的二元组的个数
struct Point
{
	int x,y,z,w,id;
	bool operator<(const Point&p)const
	{
		if(x!=p.x)return x<p.x;
		if(y!=p.y)return y<p.y;
		return z<p.z;
	}
}p[100005],tmp[100005];
int ans[100005],cnt[100005];
int tree[200005];
int lowbit(int x){return x&(-x);}
void update(int x,int w)
{
	while(x<=200000)
	{
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int sum=0;
	while(x)
	{
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}

void CDQ(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	int i=l,j=mid+1,pos=l;
	while(i<=mid&&j<=r)
	{
		if(p[i].y<=p[j].y)
		{
			update(p[i].z,p[i].w);
			tmp[pos++]=p[i++];
		}
		else
		{
			ans[p[j].id]+=query(p[j].z);
			tmp[pos++]=p[j++];
		}
	}
	while(i<=mid)
	{
		update(p[i].z,p[i].w);
		tmp[pos++]=p[i++];
	}
	while(j<=r)
	{
		ans[p[j].id]+=query(p[j].z);
		tmp[pos++]=p[j++];
	}
	for(int k=l;k<=mid;k++)update(p[k].z,-p[k].w);
	for(int k=l;k<=r;k++)p[k]=tmp[k];
}

void solve()
{
	int n,k;
	read(n,k);
	for(int i=1;i<=n;i++)
	{
		read(p[i].x,p[i].y,p[i].z);
		p[i].w=1;p[i].id=i;
	}
	sort(p+1,p+n+1);
	int tot=1;
	for(int i=2;i<=n;i++)
	{
		if(p[tot].x==p[i].x&&p[tot].y==p[i].y&&p[tot].z==p[i].z)p[tot].w++;
		else p[++tot]=p[i];
	}
	CDQ(1,tot);
	for(int i=1;i<=tot;i++)cnt[ans[p[i].id]+p[i].w-1]+=p[i].w;
	for(int i=0;i<n;i++)println(cnt[i]);
}