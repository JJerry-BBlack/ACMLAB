ll n,m,cnt=0;
ll a[1000060],root[maxn];
struct node{
	ll l,r,num;
}z[maxn];
ll clone(ll x){
	cnt++;z[cnt]=z[x];
	return cnt;
}
ll build(ll id,ll l,ll r){
	id=++cnt;
	if(l==r){
		z[cnt].num=a[l];return cnt;
	}
	ll mid=(l+r)>>1;
	z[id].l=build(z[id].l,l,mid);
	z[id].r=build(z[id].r,mid+1,r);
	return id;
}
void update(ll id1,ll &id2,ll l,ll r,ll x,ll w){
	id2=clone(id1);
	if(l>=r){
		z[id2].num=w; return;
	}
	ll mid=(l+r)>>1;
	if(x<=mid)update(z[id1].l,z[id2].l,l,mid,x,w);
	else update(z[id1].r,z[id2].r,mid+1,r,x,w);
}
ll query(ll id,ll l,ll r,ll x){
	if(l>=r)return z[id].num;  //这里要return z[id].num;
	ll mid=(l+r)>>1;
	if(x<=mid)return query(z[id].l,l,mid,x);
	else return query(z[id].r,mid+1,r,x);
}
int main(){
	n=qread(),m=qread();
	for(int i=1;i<=n;i++){
		a[i]=qread();
	}
	root[0]=build(root[0],1,n);
	for(int i=1;i<=m;i++){
		ll q=qread(),p=qread(),w=qread();
		if(p==1){
			ll k=qread();
			update(root[q],root[i],1,n,w,k);
		}else{
			root[i]=clone(root[q]);
			printf("%lld\n",query(root[q],1,n,w));
		}
	}
	return 0;
}