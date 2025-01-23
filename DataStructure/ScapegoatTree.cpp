namespace Scapegoat_Tree
{
	const double alpha=0.75;
	int ls[100005],rs[100005];
	int siz[100005],val[100005];
	int fac[100005]/*实际大小*/,cnt[100005]/*存在标记*/;
	int tot,root;
	void newnode(int&now,int w)
	{
		now=++tot;
		val[now]=w;
		siz[now]=fac[now]=1;
		cnt[now]=1;
	}
	int imbalance(int now)//判断是否平衡
	{
		if(max(siz[ls[now]],siz[rs[now]])>siz[now]*alpha
		||siz[now]-fac[now]>siz[now]*0.3)return 1;
		return 0;
	}
	vector<int>v;
	void ldr(int now)
	{
		if(!now)return;
		ldr(ls[now]);
		if(cnt[now])v.push_back(now);
		ldr(rs[now]);
	}
	void lift(int l,int r,int &now)
	{
		if(l==r)
		{
			now=v[l];
			ls[now]=rs[now]=0;
			siz[now]=fac[now]=cnt[now];
			return;
		}
		int mid=(l+r)>>1;
		now=v[mid];
		if(l<mid)lift(l,mid-1,ls[now]);
		else ls[now]=0;
		lift(mid+1,r,rs[now]);
		siz[now]=siz[ls[now]]+siz[rs[now]]+cnt[now];
		fac[now]=fac[ls[now]]+fac[rs[now]]+cnt[now];
	}
	void rebuild(int &now)//中序遍历之后拎起来
	{
		v.clear();
		ldr(now);
		if(v.empty())
		{
			now=0;
			return;
		}
		lift(0,v.size()-1,now);
	}
	void update(int now,int end)
	{
		if(!now)return;
		if(val[end]<val[now])update(ls[now],end);
		else update(rs[now],end);
		siz[now]=siz[ls[now]]+siz[rs[now]]+cnt[now];
	}
	void check(int &now,int end)
	{
		if(now==end)return;
		if(imbalance(now))
		{
			rebuild(now);
			update(root,now);
			return;
		}
		if(val[end]<val[now])check(ls[now],end);
		else check(rs[now],end);
	}
	void insert(int &now,int w)
	{
		if(!now)
		{
			newnode(now,w);
			check(root,now);
			return;
		}
		siz[now]++;
		fac[now]++;
		if(w<val[now])insert(ls[now],w);
		else if(w==val[now])cnt[now]++;
		else insert(rs[now],w);
	}
	void del(int now,int w)
	{
		if(cnt[now]&&val[now]==w)
		{
			cnt[now]--;
			fac[now]--;
			check(root,now);
			return;
		}
		fac[now]--;
		if(w<val[now])del(ls[now],w);
		else if(w==val[now])cnt[now]--;
		else del(rs[now],w);
	}
	int queryrnk(int w)
	{
		int now=root,rnk=1;
		while(now)
		{
			if(w<val[now])now=ls[now];
			else if(w==val[now])
			{
				rnk+=fac[ls[now]];
				break;
			}
			else
			{
				rnk+=cnt[now]+fac[ls[now]];
				now=rs[now];
			}
		}
		return rnk;
	}
	int querynum(int rnk)
	{
		int now=root;
		while(now)
		{
			if(cnt[now]&&fac[ls[now]]+1<=rnk&&fac[ls[now]]+cnt[now]+1>rnk)break;
			else if(fac[ls[now]]>=rnk)now=ls[now];
			else
			{
				rnk-=fac[ls[now]]+cnt[now];
				now=rs[now];
			}
		}
		return val[now];
	}
	int pre(int w)
	{
		return querynum(queryrnk(w)-1);
	}
	int sub(int w)
	{
		return querynum(queryrnk(w+1));
	}
}
using namespace Scapegoat_Tree;

void solve()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1)insert(root,x);
		else if(op==2)del(root,x);
		else if(op==3)printf("%d\n",queryrnk(x));
		else if(op==4)printf("%d\n",querynum(x));
		else if(op==5)printf("%d\n",pre(x));
		else if(op==6)printf("%d\n",sub(x));
	}
}