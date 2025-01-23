/*
1s
数组长度n，操作数m都为5e5；
五种操作：
1.给一个区间 [L,R] 加上一个数 x
2.把一个区间 [L,R] 里小于 x 的数变成 x
3.把一个区间 [L,R] 里大于 x 的数变成 x
4.求区间 [L,R] 的和
5.求区间 [L,R] 的最大值
6.求区间 [L,R] 的最小值

分别维护最小值、最大值、其他值的加标记；
区间加操作 就是把三个标记都加；区间取 min 操作就是在最大值的加标记上修改；取 max同理。

两个注意点：
以最大值上的加减标记为例。下传这个标记时要判断子区间内是否包含最大值，如果不包含则应下传其他值的加减标记；
如果一个区间的值域很小（只有 1 或 2 个数），可能会发生一个值既是最大值又是次小值这种情况，也就是发生了数域的重叠。这种情况要特判，分辨到底该被哪个标记作用。 
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int qread(){
	int s=0,w=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')w=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())s=(s<<1)+(s<<3)+(ch^48);
	return (w==-1?-s:s);}

const int INF=2e9;
int n,m;
int s[500050];
struct node{
	//最大值、次大值、最大值个数、最小值、次小值、最小值个数 
	int mx,smx,cmx,mi,smi,cmi;
	ll sum;
	//最小值、最大值、其他值的修改标记 
	int add1,add2,add3;
}tr[2000050];
#define ls (p<<1)
#define rs (p<<1|1)
void pushup(int p){
	tr[p].sum=tr[ls].sum+tr[rs].sum;
	if(tr[ls].mi==tr[rs].mi){
		tr[p].mi=tr[ls].mi;
		tr[p].smi=min(tr[ls].smi,tr[rs].smi);
		tr[p].cmi=tr[ls].cmi+tr[rs].cmi;
	}else if(tr[ls].mi<tr[rs].mi){
		tr[p].mi=tr[ls].mi;
		tr[p].smi=min(tr[ls].smi,tr[rs].mi);
		tr[p].cmi=tr[ls].cmi; 
	}else {
		tr[p].mi=tr[rs].mi;
		tr[p].smi=min(tr[ls].mi,tr[rs].smi);
		tr[p].cmi=tr[rs].cmi;
	}
	if(tr[ls].mx==tr[rs].mx){
		tr[p].mx=tr[ls].mx;
		tr[p].smx=max(tr[ls].smx,tr[rs].smx);
		tr[p].cmx=tr[ls].cmx+tr[rs].cmx; 
	}else if(tr[ls].mx>tr[rs].mx){
		tr[p].mx=tr[ls].mx;
		tr[p].smx=max(tr[ls].smx,tr[rs].mx);
		tr[p].cmx=tr[ls].cmx;
	}else {
		tr[p].mx=tr[rs].mx;
		tr[p].smx=max(tr[ls].mx,tr[rs].smx);
		tr[p].cmx=tr[rs].cmx;
	}
}
//对tr[p]的修改，k1、k2、k3 分别为最小值、最大值、其他值的标记 
void update(int p,int l,int r,int k1,int k2,int k3){
	if(tr[p].mi==tr[p].mx){
		//如果区间只有一种值，应该只作用最大值、最小值的加减标记 
		if(k1==k3)k1=k2;
		else k2=k1;
		tr[p].sum+=1LL*k1*tr[p].cmi;
	}else{
		tr[p].sum+=1LL*k1*tr[p].cmi+1LL*k2*tr[p].cmx+1LL*k3*(r-l+1-tr[p].cmi-tr[p].cmx);
	}
	//次小值为最大值，应被最大值标记作用 
	if(tr[p].smi==tr[p].mx)tr[p].smi+=k2;
	else if(tr[p].smi!=INF)tr[p].smi+=k3;//否则被其他值的标记作用
	
	if(tr[p].smx==tr[p].mi)tr[p].smx+=k1;
	else if(tr[p].smx!=INF)tr[p].smx+=k3; 
	
	tr[p].mi+=k1;tr[p].mx+=k2;
	tr[p].add1+=k1;tr[p].add2+=k2;tr[p].add3+=k3;
}
void pushdown(int p,int l,int r){
	int mi=min(tr[ls].mi,tr[rs].mi);
	int mx=max(tr[ls].mx,tr[rs].mx);
	int mid=l+r>>1;
	update(ls,l,mid,tr[ls].mi==mi?tr[p].add1:tr[p].add3,
	tr[ls].mx==mx?tr[p].add2:tr[p].add3,tr[p].add3);
	update(rs,mid+1,r,tr[rs].mi==mi?tr[p].add1:tr[p].add3,
	tr[rs].mx==mx?tr[p].add2:tr[p].add3,tr[p].add3);
	
	tr[p].add1=tr[p].add2=tr[p].add3=0;
}
void build(int p,int l,int r){
	tr[p].add1=tr[p].add2=tr[p].add3=0;
	if(l==r){
		tr[p].sum=tr[p].mi=tr[p].mx=s[l];
		tr[p].smi=INF;tr[p].smx=-INF;
		tr[p].cmi=tr[p].cmx=1;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p); 
}
void update1(int p,int l,int r,int x,int y,int w){
	if(x<=l&&r<=y){
		update(p,l,r,w,w,w);
		return;
	}
	int mid=l+r>>1;
	pushdown(p,l,r);
	if(x<=mid)update1(2*p,l,mid,x,y,w);
	if(mid<y)update1(2*p+1,mid+1,r,x,y,w);
	pushup(p);
}
void update2(int p,int l,int r,int x,int y,int w){
	if(tr[p].mi>=w)return;
	if(x<=l&&r<=y&&tr[p].smi>w){
		update(p,l,r,w-tr[p].mi,0,0);
		return;
	}
	pushdown(p,l,r);
	int mid=l+r>>1;
	if(x<=mid)update2(ls,l,mid,x,y,w);
	if(mid<y)update2(rs,mid+1,r,x,y,w);
	pushup(p);
}
void update3(int p,int l,int r,int x,int y,int w){
	if(tr[p].mx<=w)return;
	if(x<=l&&r<=y&&tr[p].smx<w){
		update(p,l,r,0,w-tr[p].mx,0);
		return;
	}
	int mid=l+r>>1;
	pushdown(p,l,r);
	if(x<=mid)update3(ls,l,mid,x,y,w);
	if(mid<y)update3(rs,mid+1,r,x,y,w);
	pushup(p);
}
ll query1(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tr[p].sum;
	int mid=l+r>>1;
	pushdown(p,l,r);
	ll ans=0;
	if(x<=mid)ans+=query1(ls,l,mid,x,y);
	if(mid<y)ans+=query1(rs,mid+1,r,x,y);
	return ans;
}
int query2(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tr[p].mx;
	int mid=l+r>>1,ans=-INF;
	pushdown(p,l,r);
	if(x<=mid)ans=max(ans,query2(ls,l,mid,x,y));
	if(mid<y)ans=max(ans,query2(rs,mid+1,r,x,y));
	return ans;
}
int query3(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tr[p].mi;
	int mid=l+r>>1,ans=INF;
	pushdown(p,l,r);
	if(x<=mid)ans=min(ans,query3(ls,l,mid,x,y));
	if(mid<y)ans=min(ans,query3(rs,mid+1,r,x,y));
	return ans; 
}
#undef ls
#undef rs
int main(){
	n=qread();
	for(int i=1;i<=n;i++)s[i]=qread();
	build(1,1,n);
	m=qread();
	while(m--){
		int op=qread(),l=qread(),r=qread();
		int x;
		if(op<=3)x=qread();
		if(op==1)update1(1,1,n,l,r,x);
		else if(op==2)update2(1,1,n,l,r,x);
		else if(op==3)update3(1,1,n,l,r,x);
		else if(op==4)printf("%lld\n",query1(1,1,n,l,r));
		else if(op==5)printf("%d\n",query2(1,1,n,l,r));
		else printf("%d\n",query3(1,1,n,l,r));
	}
	return 0;
}