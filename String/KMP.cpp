#include<bits/stdc++.h>
using namespace std;
const ll mod = 223092870;
const int MAXN = 1000005;
char s1[MAXN],s2[MAXN];
int nex[MAXN];
int main()
{
	scanf("%s%s",s1+1,s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);
	nex[1]=0;
	for(int i=2,j=0;i<=m;i++)
	{
		while(j>0&&s2[i]!=s2[j+1])j=nex[j];
		if(s2[i]==s2[j+1])j++;
		nex[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j>0&&s1[i]!=s2[j+1])j=nex[j];
		if(s1[i]==s2[j+1])j++;
		if(j==m)printf("%d\n",i-m+1),j=nex[j];
	}
	for(int i=1;i<=m;i++)printf("%d ",nex[i]);
	return 0;
}