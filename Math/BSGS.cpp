typedef long long ll;
map <ll,ll> f;
ll gcd(ll a,ll b)     //最大公约数
{
	if (!b)return a;
	return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)  //拓欧
{
	if (!b)x=1,y=0;
	else
	{
		exgcd(b,a%b,x,y);
		ll t=x;
		x=y;
		y=t-a/b*y;
	}
}
ll inv(ll a,ll b/*mod*/)    //逆元
{
	ll x,y;
	exgcd(a,b,x,y);
	return (x%b+b)%b;
}
ll poww(ll a,ll n,ll p)
{
	ll ans=1;
	while(n)
	{
		if(n&1)ans=ans*a%p;
		a=a*a%p;
		n>>=1;
	}
	return ans;
}
ll bsgs(ll a,ll b,ll p)    //BSGS算法,p为质数 a^x=b(mod p)
{
	f.clear();
	ll m=ceil(sqrt(p));
	b%=p;
	for (ll i=1;i<=m;i++)
	{
		b=b*a%p;
		f[b]=i;
	}
	ll tmp=poww(a,m,p);
	b=1;
	for (ll i=1;i<=m;i++)
	{
		b=b*tmp%p;
		if (f[b])return (i*m-f[b]+p)%p;
	}
	return -1;
}
ll exbsgs(ll a,ll b,ll p)
{
	if (b==1||p==1)return 0;     //特殊情况，x=0时最小解
	ll g=gcd(a,p),k=0,na=1;
	while (g>1)
	{
		if (b%g!=0)return -1;    //无法整除则无解
		k++;b/=g;p/=g;na=na*(a/g)%p;
		if (na==b)return k;   //na=b说明前面的a的次数为0，只需要返回k
		g=gcd(a,p);
	}
	ll ff=bsgs(a,b*inv(na,p)%p,p);
	if (ff==-1)return -1;
	return ff+k;
}