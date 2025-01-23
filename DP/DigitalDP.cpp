#include <bits/stdc++.h>
using namespace std;
int cnt=0;
int a[30];
long long dp[70][2];
long long dfs(int pos,int limit,int lead,int is6){
	if(pos==0) return 1;
	if(!limit&&dp[pos][is6]!=-1) return dp[pos][is6];
	int up=(limit?a[pos]:9);
	long long ans=0;
	for(int i=0;i<=up;i++){
		if(i==4) continue;
		if(i==2&&is6) continue;
		ans+=dfs(pos-1,limit&&(i==up),lead&&i==0,i==6);
	}
	if(!limit) dp[pos][is6]=ans;
	return ans;
}

long long solve(long long x){
	cnt=0;
	while(x){
		a[++cnt]=x%10;
		x/=10;
	}
	return dfs(cnt,1,0,0);
}

int main(){
	long long n,m;
	memset(dp,-1,sizeof(dp));
	while(scanf("%lld %lld",&n,&m)!=EOF){
		if(n==0&&m==0) break;
		printf("%lld\n",solve(m)-solve(n-1));
	}
}