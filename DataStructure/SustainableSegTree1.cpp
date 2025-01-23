ll cnt=0,n,m,len; //cnt记录当前节点数目，len代表离散化后的区间大小； 
ll a[200060],b[200050],root[200050];
struct node{
	ll l,r,num;
}z[maxn];
ll clone(ll x){
	cnt++;
	z[cnt]=z[x];
	return cnt;
}
void update(ll id1,ll &id2,ll l,ll r,ll x){
	id2=clone(id1);z[id2].num++;
	if(l>=r)return;
	ll mid=(l+r)>>1;
	if(x<=mid)update(z[id1].l,z[id2].l,l,mid,x);
	else update(z[id1].r,z[id2].r,mid+1,r,x);
}
ll query(ll id1,ll id2,ll l,ll r,ll k){
	if(l>=r)return l;
	ll mid=(l+r)>>1;
	ll num=z[z[id2].l].num-z[z[id1].l].num;
	if(k<=num)return query(z[id1].l,z[id2].l,l,mid,k);
	//这里的判断条件小心，容易出错！
	//k<=num才往左子树走
	else return query(z[id1].r,z[id2].r,mid+1,r,k-num);
}
int main(){
	n=qread(),m=qread();
	for(int i=1;i<=n;i++){
		a[i]=qread();b[i]=a[i];
	}
	sort(b+1,b+1+n);
	len=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		ll x=lower_bound(b+1,b+1+len,a[i])-b;
		update(root[i-1],root[i],1,len,x);
	}
	for(int i=1;i<=m;i++){
		ll l=qread(),r=qread(),k=qread();
		ll w=query(root[l-1],root[r],1,len,k);
		printf("%lld\n",b[w]);
	}
	return 0;
}