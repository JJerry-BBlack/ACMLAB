#include<bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
char t[1000005];
char s[1000005];
ull h[1000005],p[1000005];
ull h1[1000005];
ull get(int l,int r)
{
	return h[r]-h[l-1]*p[r-l+1];
}
ull get1(int l,int r)
{
	return h1[r]-h1[l-1]*p[r-l+1];
}
unordered_map<ull,bool>mp;
int main()
{
	scanf("%s",t+1);
	int len=strlen(t+1);
	p[0]=1;
	h[0]=0;
	for(int i=1;i<=1000000;i++)
	p[i]=p[i-1]*131;
	for(int i=1;i<=len;i++)
	h[i]=h[i-1]*131+t[i]-'a'+1;
	mp[get(1,len)]=1;
	for(int j=1;j<len;j++)
	mp[get(1,j)+get(j+1,len)*p[j]]=1;
	int _;
	scanf("%d",&_);
	while (_--)
	{
		scanf("%s",s+1);
		int l=strlen(s+1);
		h1[0]=0;
		for(int i=1;i<=l;i++)
		h1[i]=h1[i-1]*131+s[i]-'a'+1;
		int num=0;
		for(int i=1;i<=l-len+1;i++)
		if(mp[get1(i,i+len-1)])num++;
		printf("%d\n",num);
	}
	return 0;
}