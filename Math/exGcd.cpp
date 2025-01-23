int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)return x=1,y=0,a;
	int r=exgcd(b,a%b,x,y);
	tie(x,y)=make_tuple(y,x-(a/b)*y);
	return r;
}