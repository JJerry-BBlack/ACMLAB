//一个旅行者有一个最多能装V公斤的背包，现在有n件物品，已知它们的价值和所占体积。有的物品可以一次取一件，有的物品可以取无限次，有的物品可以取得个数有上限。求最大价值。

//无法理解出题人为什么非要把这三个背包放在一起，有毒吧。。。

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int m,n;
int w[1003],c[1003],s[1003],f[1003]; 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d%d",&w[i],&c[i],&s[i]);
	} 
	for(int i = 1;i <= n;i++)
	{
		if(s[i] == 0)
		{
			for(int j = w[i];j <= m;j++)
			{
				f[j] = max(f[j],f[j - w[i]] + c[i]);
			}
		}
		else{
			for(int j = 1;j <= s[i];j++)
			{
				for(int k = m;k >= w[i];k--)
				f[k] = max(f[k],f[k - w[i]] + c[i]);
			}
		}
	}
	printf("%d",f[m]);
	return 0;	
}