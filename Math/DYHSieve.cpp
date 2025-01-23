#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define fi first
#define se second
#define lowbit(x) (x&(-x))
const double eps=1e-12;
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;
int dcmp(double x){if(fabs(x)<eps)return 0;return x>0?1:-1;}

#define int ll

ll sumf1[3000005];
unordered_map<ll,ll>f1;

inline ll F1(ll n)
{
    if(n<=3e6)return sumf1[n]; // 预处理出 n 较小时的前缀和
    if(f1.count(n))return f1[n]; // 记忆化，如果求过这个值，就不需要再递归一遍了
    ll ans=n*(n+1)/2; // 这是 f * g 的 n 项前缀和
    for(ll l=2,r;l<=n;l=r+1) // 整除分块
        r=n/(n/l),ans-=(r-l+1)*F1(n/l);
        // [l,r] 的 F (n / l) 是一样的，对 g(x) 求个和即可
    return f1[n]=ans; // 别忘了除上 g(1)
}

ll sumf2[3000005];
unordered_map<ll,ll>f2;

inline ll F2(ll n)
{
    if(n<=3e6)return sumf2[n]; // 预处理出 n 较小时的前缀和
    if(f2.count(n))return f2[n]; // 记忆化，如果求过这个值，就不需要再递归一遍了
    ll ans=1; // 这是 f * g 的 n 项前缀和
    for(ll l=2,r;l<=n;l=r+1) // 整除分块
        r=n/(n/l),ans-=(r-l+1)*F2(n/l);
        // [l,r] 的 F (n / l) 是一样的，对 g(x) 求个和即可
    return f2[n]=ans; // 别忘了除上 g(1)
}

int prime[3000005];
int vis[3000005];
int len=0;

void init()
{
    sumf1[1]=sumf2[1]=1;
    for(int i=2;i<=3000000;i++)
    {
        if(!vis[i])
        {
            prime[++len]=i;
            sumf1[i]=i-1;
            sumf2[i]=-1;
        }
        for(int j=1;;j++)
        {
            long long t=1ll*prime[j]*i;
            if(t>3000000)break;
            vis[t]=1;
            if(i%prime[j]==0){sumf1[t]=sumf1[i]*prime[j];sumf2[t]=0;break;}
            else{sumf1[t]=sumf1[i]*(prime[j]-1);sumf2[t]=-sumf2[i];}
        }
    }
    for(int i=2;i<=3000000;i++)
    {
        sumf1[i]+=sumf1[i-1];
        sumf2[i]+=sumf2[i-1];
    }
}

void solve()
{
    ll n;
    cin>>n;
    cout<<F1(n)<<' '<<F2(n)<<'\n';
}

/*

*/

#undef int

int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    // cout<<fixed<<setprecision(15);

    init();

    int _;cin>>_;while(_--)
    {
        solve();
    }
    return 0;
}