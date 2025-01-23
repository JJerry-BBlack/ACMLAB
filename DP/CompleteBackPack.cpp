//有N种物品和一个容量为V的背包，每种物品都有无限件可以用。第i种物品的的费用是w[i]，价值是c[i]。求解将哪些物品装入背包的费用总和不超过背包容量，且价值总和最大。

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int m,n;
int w[1003],c[1003],f[1003]; 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d",&w[i],&c[i]);
		for(int j = w[i];j <= m;j++)//01背包是倒序，完全背包是顺序 
		{
			f[j] = max(f[j],f[j - w[i]] + c[i]);
		} 
	} 
	printf("%d",f[m]);
	return 0;	
} 