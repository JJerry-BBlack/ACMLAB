int tree[maxn][maxn];
int n,m;
int lowbit(int x){
	return x&(-x);
}
void add(int x,int y,int w){
	while(x<=n){
		for(int i=y;i<=m;i+=lowbit(i))tree[x][i]+=w;
		x+=lowbit(x);
	}
}
int sum(int x,int y){
	int res=0;
	while(x>0){
		for(int i=y;i>0;i-=lowbit(i)){
			res+=tree[x][i];
		}
		x-=lowbit(x);
	}
	return res;
}
int query(int x1,int y1,int x2,int y2){//左上右下
	return sum(x2,y2)+sum(x1-1,y1-1)-sum(x2,y1-1)-sum(x1-1,y2);
}