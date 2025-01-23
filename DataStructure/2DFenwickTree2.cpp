void update(int x1,int y1,int x2,int y2,int w){//左上右下
	add(x1,y1,w);
	add(x2+1,y1,-w);
	add(x1,y2+1,-w);
	add(x2+1,y2+1,w);
}
int query(int x,int y){
	return sum(x,y);
}