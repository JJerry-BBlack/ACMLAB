//有N种物品和一个容量为V的背包。第i种物品最多有n[i]，每件费用是w[i]，价值是c[i]。求解将哪些物品放入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。

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
		for(int j = m;j >= 0;j--)
		{
			for(int k = 0;k <= s[i];k++)
			{
				if(j - k * w[i] < 0)break;
				f[j] = max(f[j],f[j - k * w[i]] + k * c[i]);
			}
		}
	}
	printf("%d",f[m]);
	return 0;
}