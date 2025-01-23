struct Query
{
	int l,r,posl,posr,id;
	bool operator<(const Query&x)const
	{
		return (posl^x.posl)?posl<x.posl:r>x.r;
	}
}a[200005];
int b[200005],n,m;
int cnt[200005],_cnt[200005],Ans[200005];
int L[200005],R[200005];

void solve()
{
	read(n,m);
	int siz=(int)sqrt(n),T=n/siz;
	for(int i=1;i<=n;i++)read(b[i]);
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
	int ans=0;
	int laspos=0;
	for(int i=1;i<=m;i++)
	{
		if(a[i].posl==a[i].posr)
		{
			for(int j=a[i].l;j<=a[i].r;j++)_cnt[b[j]]++;
			ll tmp=0;
			while(_cnt[tmp])tmp++;
			for(int j=a[i].l;j<=a[i].r;j++)_cnt[b[j]]--;
			Ans[a[i].id]=tmp;
		}
		else
		{
			if(laspos^a[i].posl)
			{
				while(r<n)cnt[b[++r]]++;
				while(l>L[a[i].posl])cnt[b[--l]]++;
				ans=0;
				while(cnt[ans])ans++;
				while(l<L[a[i].posl])!--cnt[b[l]]?ans=min(ans,b[l++]):l++;
				laspos=a[i].posl;
			}
			while(r>a[i].r)!--cnt[b[r]]?ans=min(ans,b[r--]):r--;
			int tmp=ans;
			while(l<a[i].l)!--cnt[b[l]]?tmp=min(tmp,b[l++]):l++;
			while(l>L[a[i].posl])cnt[b[--l]]++;
			Ans[a[i].id]=tmp;
		}
	}
	for(int i=1;i<=m;i++)println(Ans[i]);
}