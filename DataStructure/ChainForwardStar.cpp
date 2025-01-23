const int maxn=200005;
struct EDGE
{
	int next,to,w;
}edge[maxn<<1];
int head[maxn];
int cnt;
void add(int u,int v,int w)
{
	edge[cnt].w=w;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt++;
}

for(int i=head[x];~i;i=edge[i].next)//遍历
{
	
}