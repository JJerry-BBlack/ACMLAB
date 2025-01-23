int n,m,q;
ll t1[maxn][maxn],t2[maxn][maxn],t3[maxn][maxn],t4[maxn][maxn];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int y,int w){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=m;j+=lowbit(j)){
			t1[i][j]+=w;
			t2[i][j]+=x*w;
			t3[i][j]+=w*y;
			t4[i][j]+=w*x*y;
		}
	}
}
void update(int x1,int y1,int x2,int y2,int w){//左上右下
	add(x1,y1,w);
	add(x1,y2+1,-w);
	add(x2+1,y1,-w);
	add(x2+1,y2+1,w);
}
ll ask(int x,int y){
	ll res=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			res+=(x+1)*(y+1)*t1[i][j]-(y+1)*t2[i][j]
			-(x+1)*t3[i][j]+t4[i][j]; 
		}
	}
	return res;
}
ll query(int x1,int y1,int x2,int y2){//左上右下
	return ask(x2,y2)-ask(x2,y1-1)-ask(x1-1,y2)+ask(x1-1,y1-1);
}