#include<bits/stdc++.h>
typedef unsigned int ui;
using namespace std;
ui h[1005][1005];
ui p1[1005],p2[1005];
ui get(int x1,int y1,int x2,int y2)
{
	return h[x2][y2]-h[x2][y1-1]*p1[y2-y1+1]-h[x1-1][y2]*p2[x2-x1+1]+h[x1-1][y1-1]*p1[y2-y1+1]*p2[x2-x1+1];
}
unordered_map<ui,bool>mp;
int main()
{
	char x;
	p1[0]=1;p2[0]=1;
	for(int i=1;i<=1000;i++)
	{
		p1[i]=p1[i-1]*131;
		p2[i]=p2[i-1]*233;
	}
	int n,m,a,b;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	getchar();
	for(int j=0;j<=m;j++)h[0][j]=0;
	for(int i=1;i<=n;i++,getchar())
	{
		h[i][0] = 0;
		for(int j=1;j<=m;j++)
		{
			x=getchar();
			h[i][j]=h[i][j-1]*131+x;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	h[i][j]+=h[i-1][j]*233;
	for(int i=1;i<=n-a+1;i++)
	for(int j=1;j<=m-b+1;j++)
	{
		ui z=get(i,j,i+a-1,j+b-1);
		if(!mp.count(z))mp[z]=1;
	}
	int _;
	scanf("%d",&_);getchar();
	while(_--)
	{
		for(int i=1;i<=a;i++,getchar())
		{
			h[i][0]=0;
			for(int j=1;j<=b;j++)
			{
				x=getchar();
				h[i][j]=h[i][j-1]*131+x;
			}
		}
		for(int i=1;i<=a;i++)
		h[i][b]+=h[i-1][b]*233;
		if(mp.count(h[a][b]))printf("1\n");
		else printf("0\n");
	}
	return 0;
}