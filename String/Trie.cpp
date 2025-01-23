#include<bits/stdc++.h>
using namespace std;
int trie[500005][30];
int color[500005];
int k=1;
void insert(char *w)
{
	int len=strlen(w);
	int p=0;
	for(int i=0;i<len;i++)
	{
		int c=w[i]-'a';
		if(!trie[p][c])
		trie[p][c]=k++;
		p=trie[p][c];
	}
	color[p]=1;
}
int search(char *s)
{
	int len=strlen(s);
	int p=0;
	for(int i=0;i<len;i++)
	{
		int c=s[i]-'a';
		if(!trie[p][c])return 0;
		p=trie[p][c];
	}
	if(color[p]==1){color[p]=2;return 1;}
	else if(color[p]==2)return 2;
	else return 0;
}
char str[55];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		insert(str);
	}
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",str);
		int res=search(str);
		if(!res)printf("WRONG\n");
		else if(res==1)printf("OK\n");
		else printf("REPEAT\n");
	}
	return 0;
}