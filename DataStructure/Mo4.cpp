struct Query
{
	int l,r,posl,posr,id;
	bool operator<(const Query&x)const
	{
		return (posl^x.posl)?posl<x.posl:r<x.r;
	}
}a[100005];
int b[100005],d[100005],cntd,n,m;
ll cnt[100005],_cnt[100005],Ans[100005];
int L[100005],R[100005];

void solve()
{
	read(n,m);
	int siz=(int)sqrt(n),T=n/siz;
	for(int i=1;i<=n;i++)
	{
		read(b[i]);
		d[++cntd]=b[i];
	}
	sort(d+1,d+cntd+1);
	cntd=unique(d+1,d+cntd+1)-d-1;
	for(int i=1;i<=n;i++)
	b[i]=lower_bound(d+1,d+cntd+1,b[i])-d;
	for(int i=1;i<=T;i++)
	{
		if(i*siz>n)break;
		L[i]=(i-1)*siz+1;
		R[i]=i*siz;
	}
	if(R[T]<n)T++,L[T]=R[T-1]+1,R[T]=n;
	for(int i=1;i<=m;i++)
	{
		read(a[i].l,a[i].r);
		a[i].posl=(a[i].l-1)/siz+1;
		a[i].posr=(a[i].r-1)/siz+1;
		a[i].id=i;
	}
	sort(a+1,a+m+1);
	int l=1,r=0;
	ll ans=0;
	int laspos=0;
	for(int i=1;i<=m;i++)
	{
		if(a[i].posl==a[i].posr)
		{
			for(int j=a[i].l;j<=a[i].r;j++)_cnt[b[j]]++;
			ll tmp=0;
			for(int j=a[i].l;j<=a[i].r;j++)
			tmp=max(tmp,_cnt[b[j]]*d[b[j]]);
			for(int j=a[i].l;j<=a[i].r;j++)_cnt[b[j]]--;
			Ans[a[i].id]=tmp;
		}
		else
		{
			if(laspos^a[i].posl)
			{
				while(l<R[a[i].posl]+1)cnt[b[l++]]--;
				while(l>R[a[i].posl]+1)cnt[b[--l]]++;
				while(r>R[a[i].posl])cnt[b[r--]]--;
				while(r<R[a[i].posl])
				ans=0,laspos=a[i].posl;
			}
			while(r<a[i].r)ans=max(ans,++cnt[b[++r]]*d[b[r]]);
			ll tmp=ans;
			while(l>a[i].l)tmp=max(tmp,++cnt[b[--l]]*d[b[l]]);
			while(l<R[a[i].posl]+1)cnt[b[l++]]--;
			Ans[a[i].id]=tmp;
		}
	}
	for(int i=1;i<=m;i++)println(Ans[i]);
}