//一个旅行者有一个最多能装M公斤的背包，现在有n件物品，它们的重量分别是W1，W2......Wn；它们的价格为C1，C2......Cn，求旅行者能获得的最大总价值.

#include<bits/stdc++.h>
using namespace std;
int w[1003],c[1003],f[1003];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d",&w[i],&c[i]);
		for(int j = m;j >= w[i];j--)
		{
			f[j] = max(f[j],f[j - w[i]] + c[i]);
		}
	} 
	printf("%d",f[m]);
	return 0;
}