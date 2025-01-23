#include<bits/stdc++.h>
#define int64 long long
using namespace std;
const int64 mod=1e9+7;
int64 a[410][410];
int n,is[410],js[410];
void exgcd(int a,int b,int &x,int &y){
	if(!b)return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=x*(a/b);
}
int inv(int p){
	int x,y;exgcd(p,mod,x,y);
	return (x+mod)%mod;
}
void inv(){
	for(int k=1;k<=n;k++){
		for(int i=k;i<=n;i++) // 1
		for(int j=k;j<=n;j++)if(a[i][j]){
			is[k]=i,js[k]=j;break;
		}
		for(int i=1;i<=n;i++) // 2
		swap(a[k][i],a[is[k]][i]);
		for(int i=1;i<=n;i++)
		swap(a[i][k],a[i][js[k]]);
		if(!a[k][k]){
			puts("No Solution");
			exit(0);
		}
		a[k][k]=inv(a[k][k]); // 3
		for(int j=1;j<=n;j++)if(j!=k) // 4
		(a[k][j]*=a[k][k])%=mod;
		for(int i=1;i<=n;i++)if(i!=k) // 5
		for(int j=1;j<=n;j++)if(j!=k)
		(a[i][j]+=mod-a[i][k]*a[k][j]%mod)%=mod;
		for(int i=1;i<=n;i++)if(i!=k) // 就是这里不同
		a[i][k]=(mod-a[i][k]*a[k][k]%mod)%mod;
	}
	for(int k=n;k;k--){ // 6
		for(int i=1;i<=n;i++)
		swap(a[js[k]][i],a[k][i]);
		for(int i=1;i<=n;i++)
		swap(a[i][is[k]],a[i][k]);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	scanf("%lld",a[i]+j);
	inv();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	printf("%lld%c",a[i][j],j==n?'\n':' ');
	return 0;
}