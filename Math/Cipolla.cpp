struct cipolla
{
	ll n,p,w2,a;//w2=a*a-n mod p
	
	struct cx{ll x,y;};//Fp2 = {x+yw | x,y belon to Fp}
	cx mul(cx a,cx b){return (cx){(a.x*b.x+a.y*b.y%p*w2)%p,(a.x*b.y+a.y*b.x)%p};}
	cx cx_poww(cx a,int n)
	{
		cx ans=(cx){1,0};
		while(n)
		{
			if(n&1)ans=mul(ans,a);
			a=mul(a,a);n>>=1;
		}
		return ans;
	}
	void getsol(ll _n,ll _p,ll&ans1,ll&ans2)
	{
		n=_n,p=_p;
		ans1=ans2=-1;//最多两个解,无解是-1
		if(n==0||p==2){ans1=n;return;}
		
		if(poww((ll)n,(ll)(p-1)/2,(ll)p)==p-1)return;
		
		for(a=rand()%p;;a==p-1?(a=0):(++a))
		{
			if(poww((a*a-n+p)%p,(p-1)/2,p)==p-1)
			{
				w2=(a*a-n+p)%p;
				break;
			}
		}
		cx b=(cx){a,1};
		b=cx_poww(b,(p+1)/2);
		ans1=b.x;
		if(ans1!=p-ans1)ans2=p-ans1;
		return;
	}
};