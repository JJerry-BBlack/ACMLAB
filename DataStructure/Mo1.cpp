struct Query
{
	int l,r,id,pos;
	bool operator<(const Query &x)const
	{
		return (pos^x.pos)?pos<x.pos:(pos&1)?r<x.r:r>x.r;
	}
}a[100005];
int b[100005],n,m;
ll cnt[100005],Ans[100005];

void solve()
{
	read(n,m);
	int siz=n/sqrt(m);
	if(!siz)siz++;
	for(int i=1;i<=n;i++)read(b[i]);
	for(int i=1;i<=m;i++)
	{
		read(a[i].l,a[i].r);
		a[i].pos=(a[i].l-1)/siz+1;
		a[i].id=i;
	}
	sort(a+1,a+m+1);
	int l=1,r=0;
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		while(l>a[i].l)ans+=(++cnt[b[--l]]==2);
		while(r<a[i].r)ans+=(++cnt[b[++r]]==2);
		while(l<a[i].l)ans-=(--cnt[b[l++]]==1);
		while(r>a[i].r)ans-=(--cnt[b[r--]]==1);
		Ans[a[i].id]=ans;
	}
	for(int i=1;i<=m;i++)
	{
		if(Ans[i])println("No");
		else println("Yes");
	}
}