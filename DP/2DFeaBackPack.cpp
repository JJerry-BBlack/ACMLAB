//小橙书上关于这个讲了一大堆，大意就是限制条件有之前的一个变成了两个，就是由之前得背包重量，变成了现在的氢气和氧气的含量。

//例题：潜水员

//潜水员有一个带2种气体的气缸：一个为氧气，一个为氮气。他有一定数量的气缸。每个气缸都有重量和气体容量。潜水员为了完成他的工作需要特定数量的氧和氢。他完成工作所需气缸的总重的最低限度是多少

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
//啊啊啊de了一万年bug终于过了
int u,v,k;
int f[101][101];
int a[1001],b[1001],c[1001];
int main()
{
	memset(f,10001,sizeof(f));//要把数组初始化为一个很大的数
	f[0][0] = 0;
	scanf("%d%d%d",&v,&u,&k);
	for(int i = 1;i <= k;i++)
	{
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	}
	for(int i = 1;i <= k;i++)
	{
		for(int j = v;j >= 0;j--)
		{
			for(int x = u;x >= 0;x--)
			{
				int t1 = j + a[i],t2 = x + b[i];//设一个变量方便计算
				if(t1 > v)t1 = v;//如果超出需求量就用需求量代替
				if(t2 > u)t2 = u;//这样就可以用f[v][u]来表示最优解了
				f[t1][t2] = min(f[t1][t2],f[j][x] + c[i]);
			}
		}
	}
	printf("%d",f[v][u]);
	return 0;
} 
/*
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
*/
//正解是最后输出249