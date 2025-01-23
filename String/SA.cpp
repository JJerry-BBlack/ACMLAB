template<int N>
struct suffixarray
{
	char s[N];
	int rk[N],sa[N],ht[N],tmp[N],cnt[N];
	// n:串长  m:字符集大小  s[0..n-1]:字符串  sa[1..n]:字典序第 i 小的是哪个后缀
	// rk[0..n-1]:后缀 i 的排名  ht[i]:lcp(sa[i],sa[i-1])
	void build(int n,int m)
	{
		int i,j,k;n++;
		for(i=0;i<n*2+5;i++)rk[i]=sa[i]=ht[i]=tmp[i]=0;
		for(i=0;i<m;i++)cnt[i]=0;
		for(int i=0;i<n;i++)cnt[rk[i]=s[i]]++;
		for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
		for(i=0;i<n;i++)sa[--cnt[rk[i]]]=i;
		for(k=1;k<=n;k<<=1)
		{
			for(i=0;i<n;i++)
			{
				j=sa[i]-k;
				if(j<0)j+=n;
				tmp[cnt[rk[j]]++]=j;
			}
			sa[tmp[cnt[0]=0]]=j=0;
			for(i=1;i<n;i++)
			{
				if(rk[tmp[i]]!=rk[tmp[i-1]]||rk[tmp[i]+k]!=rk[tmp[i-1]+k])
					cnt[++j]=i;
				sa[tmp[i]]=j;
			}
			memcpy(rk,sa,n*sizeof(int));
			memcpy(sa,tmp,n*sizeof(int));
			if(j>=n-1)break;
		}
		for(j=rk[ht[i=k=0]=0];i<n-1;i++,k++)
			while(~k&&s[i]!=s[sa[j-1]+k])ht[j]=k--,j=rk[sa[j]+1];
	}
	void debug(int n)
	{
		cout<<"sa:";for(int i=1;i<=n;i++)cout<<sa[i]<<" \n"[i==n];
		cout<<"rk:";for(int i=0;i<n;i++)cout<<rk[i]<<" \n"[i==n-1];
		cout<<"ht:";for(int i=1;i<=n;i++)cout<<ht[i]<<" \n"[i==n];
	}
	int mi[__lg(N)+1][N];
	void rmqinit(int n)
	{
		for(int i=1;i<=n;i++)
		{
			mi[0][i]=ht[i];
		}
		for(int i=1;i<=__lg(n);i++)
		{
			for(int j=1;j+(1<<i)-1<=n;j++)
			{
				mi[i][j]=min(mi[i-1][j],mi[i-1][j+(1<<(i-1))]);
			}
		}
	}
	int query(int l,int r)
	{
		int k=__lg(r-l+1);
		return min(mi[k][l],mi[k][r-(1<<k)+1]);
	}
	int Query(int L,int R)
	{
		int l=min(rk[L],rk[R]);
		int r=max(rk[L],rk[R]);
		return query(l+1,r);
	}
	int cmp(int l1,int r1,int l2,int r2)
	{
		int len=Query(l1,l2);
		if(r1-l1+1<=len&&r2-l2+1<=len)return 0;// ==
		else if(r1-l1+1<=len)return -1;// <
		else if(r2-l2+1<=len)return 1;// >
		else
		{
			if(s[l1+len]>s[l2+len])return 1;// >
			else return -1;// <
		}
	}
};

suffixarray<200005>sa;