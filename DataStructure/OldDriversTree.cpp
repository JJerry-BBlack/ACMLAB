/*
例题:
操作1: 区间加x
操作2: 区间赋值x
操作3: 求区间第K大
操作4: 求区间的x幂和 模y;
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct node{
	int l,r;
	mutable ll val;
	bool operator < (const node &ths)const{
		return l<ths.l;
	}
	node(int L,int R,ll Val):l(L),r(R),val(Val){}
	node(int L):l(L){}
};

set<node>s;
using si=set<node>::iterator;

si split(int pos){
	si it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos)return it;
	--it;
	int l=it->l,r=it->r;
	ll val=it->val;
	s.erase(it);
	s.insert(node(l,pos-1,val));
	return s.insert(node(pos,r,val)).first;
}
void assign(int l,int r,int val){
	si itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,val));
}
void add(int l,int r,ll val){
	si itr=split(r+1),itl=split(l);
	for(si it=itl;it!=itr;++it)
	it->val+=val; 
}
ll kth(int l,int r,int k){
	si itr=split(r+1),itl=split(l);
	vector<pair<ll,int>>v;
	v.clear();
	for(si it=itl;it!=itr;++it)
	v.push_back(pair<ll,int>(it->val,it->r-it->l+1));
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++){
		k-=v[i].second;
		if(k<=0)return v[i].first; 
	}
	return -1; 
}
ll query(int l,int r,int x,int y){
	si itr=split(r+1),itl=split(l);
	ll res=0;
	for(si it=itl;it!=itr;++it)
	res=(res+(it->r-it->l+1)*qp(it->val,x,y)%y)%y; 
	return res;
}
int n,m,vmax;
ll seed;
int rnd(){
	int ret=(int)seed;
	seed=(seed*7+13)%1000000007;
	return ret;
}
int main(){
	scanf("%d%d%lld%d",&n,&m,&seed,&vmax);
	for(int i=1;i<=n;i++){
		int a=rnd()%vmax+1;
		s.insert(node(i,i,a));
	} 
	s.insert(node(n+1,n+1,0));
	for(int i=1;i<=m;i++){
		int l,r,x,y;
		int op=rnd()%4+1;
		l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)swap(l,r); 
		if(op==3)x=rnd()%(r-l+1)+1;
		else x=rnd()%vmax+1;
		if(op==4)y=rnd()%vmax+1;
		if(op==1)add(l,r,x);
		else if(op==2)assign(l,r,x);
		else if(op==3)printf("%lld\n",kth(l,r,x));
		else printf("%lld\n",query(l,r,x,y));
	}
}