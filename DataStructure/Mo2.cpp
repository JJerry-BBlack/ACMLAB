struct Query
{
	int l,r,t,id,posl,posr;
	bool operator<(const Query &x)const
	{
		return (posl^x.posl)?posl<x.posl:((posr^x.posr)?posr<x.posr:t<x.t);
	}
}a[200005];
struct Replace
{
	int p,col;
}c[200005];
int b[200005],n,m;
int cnta,cntc;
ll cnt[1000005],Ans[200005];

void solve()
{
	read(n,m);
	int siz=pow(n,2.0/3.0);
	for(int i=1;i<=n;i++)read(b[i]);
	for(int i=1;i<=m;i++)
	{
		string s;int x,y;
		read(s,x,y);
		if(s=="Q")
		{
			a[++cnta].l=x;a[cnta].r=y;
			a[cnta].t=cntc;a[cnta].id=cnta;
			a[cnta].posl=(a[cnta].l-1)/siz+1;
			a[cnta].posr=(a[cnta].r-1)/siz+1;
		}
		else{c[++cntc].p=x;c[cntc].col=y;}
	}
	sort(a+1,a+cnta+1);
	int l=1,r=0,t=0;ll ans=0;
	for(int i=1;i<=m;i++)
	{
		while(l<a[i].l)ans-=!--cnt[b[l++]];
		while(l>a[i].l)ans+=!cnt[b[--l]]++;
		while(r<a[i].r)ans+=!cnt[b[++r]]++;
		while(r>a[i].r)ans-=!--cnt[b[r--]];
		while(t<a[i].t)
		{
			t++;
			if(a[i].l<=c[t].p&&c[t].p<=a[i].r)
			ans-=!--cnt[b[c[t].p]]-!cnt[c[t].col]++;
			swap(b[c[t].p],c[t].col);
		}
		while(t>a[i].t)
		{
			if(a[i].l<=c[t].p&&c[t].p<=a[i].r)
			ans-=!--cnt[b[c[t].p]]-!cnt[c[t].col]++;
			swap(b[c[t].p],c[t].col);
			t--;
		}
		Ans[a[i].id]=ans;
	}
	for(int i=1;i<=cnta;i++)println(Ans[i]);
}