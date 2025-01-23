int root=1;
template<typename T,int Sz,int Rng>
struct DynamicSegTree
{
    int cnt=1;
    T val[Sz];
    int ls[Sz];
    int rs[Sz];
    void clear(){cnt=1;}
    int newnode()
    {
        cnt++;
        ls[cnt]=rs[cnt]=0;
        val[cnt]=0;
        return cnt;
    }
    void update(T w,int x,int y,int&p=root,int l=1,int r=Rng)
    {
        if(!p)p=newnode();
        if(x<=l&&r<=y)
        {
            val[p]+=w;
        }
        else
        {
            int mid=(l+r)>>1;
            if(x<=mid)update(w,x,y,ls[p],l,mid);
            if(mid<y)update(w,x,y,rs[p],mid+1,r);
        }
    }
    T query(int x,int p=root,int l=1,int r=Rng,T ans=0)
    {
        if(!p)return ans;
        ans+=val[p];
        if(l==r)return ans;
        else
        {
            int mid=(l+r)>>1;
            if(x<=mid)return query(x,ls[p],l,mid,ans);
            else return query(x,rs[p],mid+1,r,ans);
        }
    }
};

DynamicSegTree<int,40000005,1000000000>seg;