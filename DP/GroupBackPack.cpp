//有完没完，难道我真的要把自己的大好人生都用来学习背包吗！！！

//问题：

//有N件物品和一个容量为V的背包。第i件物品的费用是w[ i ],价值是c[ i ]。这些物品被划分为若干组，每组中的物品互相冲突，最多选一件。求解将哪些物品放入背包中可使这鞋物品的费用总和不超过背包容量，且价值总和最大

//对每一组物品，可以选择其中的一件或者一件都不选

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
//这段代码简直有毒，我照着小橙书一个字一个字地敲得，结果竟然过不了样例
int v,n,t;
int w[33],c[33];
int a[13][33],dp[203];
int main()
{
	scanf("%d%d%d",&v,&n,&t);
	for(int i = 1;i <= n;i++)
	{
		int p;
		scanf("%d%d%d",&w[i],&c[i],&p);
		a[p][++a[p][0]] = i;//记录下来它属于哪个组 
	}
	for(int x = 1;x <= t;x++)
	{
		for(int j = v;j >= 0;j--)
		{
			for(int i = 1;i <= a[x][0];i++)
			{
				if(j >= w[a[x][i]])
				{
					int q = a[x][i];
					dp[j] = max(dp[j - w[q]] + c[q],dp[j]);
				}
			}
		}
	}
	printf("%d",dp[v]);
	return 0;
}
/*
10 6 3
2 1 1
3 3 1
4 8 2
6 9 2
2 8 3
3 9 3
*/

//输出20