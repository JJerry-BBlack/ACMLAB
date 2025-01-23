/*
1s
长度 n,询问 m 都为 1e6
两种操作：
1 x y——将第 x 个数变为 y；
2 y——将所有小于 y 的数修改为 y；
*/
#include<bits/stdc++.h>
using namespace std;

inline int qread(){
	int s=0,w=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')w=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())s=(s<<1)+(s<<3)+(ch^48);
	return (w==-1?-s:s);}

int n,m;
int a[200050];
struct node{
	int mi,smi,cnt,tag;
}tr[800050];
void pushup(int p){
	if(tr[2*p].mi<tr[2*p+1].mi){
		tr[p].mi=tr[2*p].mi;tr[p].cnt=tr[2*p].cnt;
		tr[p].smi=min(tr[2*p+1].mi,tr[2*p].smi);
	}else if(tr[2*p].mi>tr[2*p+1].mi){
		tr[p].mi=tr[2*p+1].mi;tr[p].cnt=tr[2*p+1].cnt;
		tr[p].smi=min(tr[2*p].mi,tr[2*p+1].smi);
	}else {
		tr[p].mi=tr[2*p].mi;tr[p].cnt=tr[2*p].cnt+tr[2*p+1].cnt;
		tr[p].smi=min(tr[2*p].smi,tr[2*p+1].smi);
	}
}
void build(int p,int l,int r){
	tr[p].tag=-1;
	if(l==r){
		tr[p].mi=a[l];
		tr[p].smi=1e9+7;
		tr[p].cnt=1;
		return;
	}
	int mid=l+r>>1;
	build(2*p,l,mid);
	build(2*p+1,mid+1,r);
	pushup(p);
}
void pushdown(int p){
	if(tr[p].tag==-1)return ;
	if(tr[p].tag>tr[2*p].mi){
		tr[2*p].mi=tr[2*p].tag=tr[p].tag;
	}
	if(tr[p].tag>tr[2*p+1].mi){
		tr[2*p+1].mi=tr[2*p+1].tag=tr[p].tag;
	}
	tr[p].tag=-1;
} 
void update(int p,int l,int r,int w){
	if(tr[p].mi>=w)return;
	if(tr[p].smi>w){
		tr[p].mi=tr[p].tag=w;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	update(2*p,l,mid,w);update(2*p+1,mid+1,r,w);
	pushup(p);
}
void update1(int p,int l,int r,int x,int w){
	if(l==r){
		tr[p].mi=w;
		return;
	}
	int mid=l+r>>1;pushdown(p);
	if(x<=mid)update1(2*p,l,mid,x,w);
	else update1(2*p+1,mid+1,r,x,w);
	pushup(p);
}
int query(int p,int l,int r,int x){
	if(l==r)return tr[p].mi;
	int mid=l+r>>1;
	pushdown(p);
	if(x<=mid)return query(2*p,l,mid,x);
	else return query(2*p+1,mid+1,r,x); 
}
int main()
{
	n=qread();
	for(int i=1;i<=n;i++){
		a[i]=qread();
	}
	build(1,1,n);
	m=qread();
	for(int i=1;i<=m;i++){
		int op;
		op=qread();
		if(op==1){
			int a,b;
			a=qread();b=qread();
			update1(1,1,n,a,b);
		}else {
			int a;a=qread();
			update(1,1,n,a);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",query(1,1,n,i));
	}
	return 0;
}