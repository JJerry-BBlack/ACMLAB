//求p[i].x<=p[j].x&&p[i].y<=p[j].y&&i!=j的二元组的个数(此题y已有序)
struct Point
{
	int x,id;
}p[15005],tmp[15005];
int ans[15005],cnt[15005];

void CDQ(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	int i=l,j=mid+1,pos=l;
	while(i<=mid&&j<=r)
	{
		if(p[i].x<=p[j].x)tmp[pos++]=p[i++];
		else{ans[p[j].id]+=i-l;tmp[pos++]=p[j++];}
	}
	while(i<=mid)tmp[pos++]=p[i++];
	while(j<=r){ans[p[j].id]+=i-l;tmp[pos++]=p[j++];}
	for(int k=l;k<=r;k++)p[k]=tmp[k];
}

void solve()
{
	int n;
	while(read(n))
	{
		for(int i=1;i<=n;i++)
		{
			ans[i]=cnt[i-1]=0;
			int b;read(p[i].x,b);
			p[i].id=i;
		}
		CDQ(1,n);
		for(int i=1;i<=n;i++)cnt[ans[p[i].id]]++;
		for(int i=0;i<n;i++)println(cnt[i]);
	}
}