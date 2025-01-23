/*
给定n个点的无向完全图，
给出每个点的点权ai，
两点之间的边权是两点权异或值，
求最小生成树
ai<2^30
复杂度o(nlogn)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;

struct
{
    int nxt[2];
}trie[8000005];
int cnt;

void Insert(int x)
{
    int now=0;
    for(int i=29;i>=0;i--)
    {
        int t=(x>>i)&1;
        if(!trie[now].nxt[t])trie[now].nxt[t]=++cnt;
        now=trie[now].nxt[t];
    }
}
ll Find_MIN(int x)
{
    ll ans=0;
    int now=0;
    for(int i=29;i>=0;i--)
    {
        int t=(x>>i)&1;
        if(trie[now].nxt[t])
        {
            now=trie[now].nxt[t];
        }
        else
        {
            now=trie[now].nxt[t^1];
            ans|=1<<i;
        }
    }
    return ans;
}

int a[200005];
ll fenzhi(int *a,int l,int r,int id)
{
    if(l>=r||id==-1)return 0;
    int mid=r;
    while(mid>=l&&((a[mid]>>id)&1))mid--;
    ll ans=0;
    ans+=fenzhi(a,l,mid,id-1);
    ans+=fenzhi(a,mid+1,r,id-1);
    if(mid==l-1||mid==r)return ans;
    for(int i=l;i<=mid;i++)Insert(a[i]);
    ll minn=1e18;
    for(int i=mid+1;i<=r;i++)minn=min(minn,Find_MIN(a[i]));
    ans+=minn;
    for(int i=0;i<=cnt;i++)trie[i].nxt[0]=trie[i].nxt[1]=0;
    cnt=0;
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    ll ans=fenzhi(a,1,n,29);//29是位数
    printf("%lld\n",ans);
    return 0;
}