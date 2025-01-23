template<typename T,int N>
struct fenwick
{
    T a[N];
    void clear(int _siz)
    {
        _siz=min(_siz,N);
        for(int i=0;i<_siz;i++)a[i]=0;
    }
    void update(T w,int x)
    {
        if(x<=0||x>=N)return;
        while(x<N)
        {
            a[x]+=w;
            x+=lowbit(x);
        }
    }
    T query(int x)
    {
        T ans=0;
        if(x<=0||x>=N)return ans;
        while(x)
        {
            ans+=a[x];
            x-=lowbit(x);
        }
        return ans;
    }
};
fenwick<int,500005>tr;