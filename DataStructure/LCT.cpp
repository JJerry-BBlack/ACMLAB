//0 x y 代表询问从x到y的路径上的点的权值的xor和。保证x到y是联通的。
//1 x y 代表连接x到y，若x到y已经联通则无需连接。
//2 x y 代表删除边(x,y)，不保证边(x,y)存在。
//3 x y 代表将点x上的权值变成y。
#include<bits/stdc++.h>
using namespace std;

#define ll long long
//#define int ll
constexpr int inf=0x3f3f3f3f;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;

constexpr int N=500005;

struct Link_Cut_Tree
{
	#define get(x) (son[1][fa[x]]==x)//获取x是父亲的那个儿子
	int son[2][N],fa[N],siz[N],val[N];
	inline void pushup(int x)
	{
		siz[x]=siz[son[0][x]]^siz[son[1][x]]^val[x];
	}
	bool rev[N];
	inline void pushdown(int x)
	{
		if(!rev[x])return;
		rev[son[0][x]]^=1;rev[son[1][x]]^=1;
		swap(son[0][x],son[1][x]);rev[x]=0;
	}
	inline bool isroot(int x)//判断x是否是所在树的根
	{
		return !(son[0][fa[x]]==x||son[1][fa[x]]==x);
	}
	inline void rotate(int x)//将x向上旋转一层的操作
	{
		int y=fa[x],z=fa[y];
		if(!isroot(y))son[y==son[1][z]][z]=x;
		bool is=(son[1][y]==x);
		son[is][y]=son[!is][x];fa[son[!is][x]]=y;
		son[!is][x]=y;fa[y]=x;fa[x]=z;pushup(y);pushup(x);
	}
	int stk[N],top;
	inline void splay(int x)//通过和rotate操作联动实现把x转移到当前splay的根
	{
		stk[++top]=x;
		for(int i=x;!isroot(i);i=fa[i])stk[++top]=fa[i];
		while(top)pushdown(stk[top--]);
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];//cout<<x<<" "<<y<<" "<<z<<endl;
			if(!isroot(y))
			{
				if((son[1][y]==x)^(son[1][z]==y))rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	inline int access(int x)//把从根到x的所有点放在一条实链里,使根到x成为一条实路径,并且在同一棵splay里
	{
		int p;
		for(p=0;x;p=x,x=fa[x])
		splay(x),son[1][x]=p,pushup(x);
		return p;
		//连续两次access操作时,第二次access操作的返回值等于这两个节点的LCA
		//表示x到根的链所在的splay树的根.这个节点一定已经被旋转到了根节点,且父亲一定为空
	}
	void update(int x)//在access操作之后,递归地从上到下pushdown信息
	{
		if(!isroot(x))update(fa[x]);
		pushdown(x);
	}
	inline void makeroot(int x)//使x点成为其所在树的根
	{
		access(x);splay(x);rev[x]^=1;
	}
	inline int find(int x)//找到x所在树的根节点编号
	{
		access(x);splay(x);
		while(son[0][x])x=son[0][x];
		return x;
	}
	inline void link(int x,int y)//把x,y两点间连一条边
	{
		if(find(x)==find(y))return;
		makeroot(x);fa[x]=y;
	}
	inline void split(int x,int y)//提取出x,y间的路径,方便做区间操作,并以y为根
	{
		makeroot(x);access(y);splay(y);
	}
	inline void cut(int x,int y)//把x,y两点间边删掉
	{
		split(x,y);
		if(son[0][y]==x&&son[1][x]==0)son[0][y]=fa[x]=0;
	}
	inline int lca(int x,int y)//求两点LCA
	{
		access(x);splay(x);
		return access(y);
	}
}T;

void solve()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&T.val[i]);
		T.siz[i]=T.val[i];
	}
	for(int i=1;i<=m;i++)
	{
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(op==0)T.split(x,y),printf("%d\n",T.siz[y]);
		else if(op==1)T.link(x,y);
		else if(op==2)T.cut(x,y);
		else T.makeroot(x),T.val[x]=y,T.pushup(x);
	}
}

signed main()
{
	//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	
	
	//	int _;scanf("%d",&_);while(_--)
	solve();
	return 0;
}