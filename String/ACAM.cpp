#include<bits/stdc++.h>
using namespace std;
const int MAXN=2000005;
int trie[MAXN][26];
int ed[MAXN];
int fail[MAXN];
int mp[200005];
int tot=0;
int ans[200005];
int vis[200005];
int in[200005];
void insert(char *s,int num)
{
    int len=strlen(s),p=0;
    for(int i=0;i<len;i++)
    {
        int ch=s[i]-'a';
        if(trie[p][ch]==0)trie[p][ch]=++tot;
        p=trie[p][ch];
    }
    if(!ed[p])ed[p]=num;
    mp[num]=ed[p];
}
void build()
{
    queue<int>q;
    memset(fail,0,sizeof(fail));
    for(int i=0;i<26;i++)if(trie[0][i])q.push(trie[0][i]);
    while(!q.empty())
    {
        int fa=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(trie[fa][i])
            {
                fail[trie[fa][i]]=trie[fail[fa]][i];
                in[fail[trie[fa][i]]]++;
                q.push(trie[fa][i]);
            }
            else
            {
                trie[fa][i]=trie[fail[fa]][i];
            }
        }
    }
}
void TopologicalSort()
{
    queue<int>q;
    for(int i=1;i<=tot;i++)if(!in[i])q.push(i);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[ed[u]]=ans[u];
        int v=fail[u];
        in[v]--;
        ans[v]+=ans[u];
        if(!in[v])q.push(v);
    }
}
void query(char *s)
{
    int len=strlen(s);
    int p=0;
    for(int i=0;i<len;i++)
        p=trie[p][s[i]-'a'],ans[p]++;
}
char s[200005];
char str[2000005];
int main()
{
    int n;
    scanf("%d",&n);
    tot=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        insert(s,i);
    }
    build();
    scanf("%s",str);
    query(str);
    TopologicalSort();
    for(int i=1;i<=n;i++)printf("%d\n",vis[mp[i]]);
    return 0;
}