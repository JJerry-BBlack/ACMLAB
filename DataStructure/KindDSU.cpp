#include<bits/stdc++.h>
using namespace std;
int fa[150005];
int findd(int x)
{
	return fa[x]==x?x:fa[x]=findd(fa[x]);
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=3*n;i++)fa[i]=i;
	int ans=0;
	for(int i=1;i<=k;i++)
	{
		int d,x,y;
		scanf("%d%d%d",&d,&x,&y);
		if(x>n||y>n){ans++;continue;}
		if(d==1)
		{
			if(findd(x)==findd(y+n)||findd(x)==findd(y+2*n)){ans++;continue;}
			fa[findd(y)]=findd(x);
			fa[findd(y+n)]=findd(x+n);
			fa[findd(y+2*n)]=findd(x+2*n);
		}
		else
		{
			if(findd(x)==findd(y+2*n)||findd(x)==findd(y)){ans++;continue;}
			fa[findd(y+n)]=findd(x);
			fa[findd(y+2*n)]=findd(x+n);
			fa[findd(y)]=findd(x+2*n);
		}
	}
	printf("%d\n",ans);
	return 0;
}