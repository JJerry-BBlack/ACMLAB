// a[1],a[2],...,a[n] in [0,1]
// operation 1: forall i in [l,r], 0 -> 1, 1 -> 0
// operation 2: calc the inversion of [l,r]

struct S
{
    ll zero,one,inversion;
};

struct F
{
    bool f;
};

S op(S l,S r)
{
    return S{l.zero+r.zero,l.one+r.one,l.inversion+r.inversion+l.one*r.zero};
}

S e(){return S{0,0,0};}

S mapping(F l,S r)
{
    if(!l.f)return r;
    return S{r.one,r.zero,r.zero*r.one-r.inversion};
}

F composition(F l,F r){return F{(!l.f&&r.f)||(l.f&&!r.f)};}

F id(){return F{false};}

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<S>a(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        a[i]=S{x==0,x==1,0};
    }

    lazy_segtree<S,op,e,F,mapping,composition,id>seg(a);

    for(int i=0;i<q;i++)
    {
        int t,l,r;
        cin>>t>>l>>r;
        if(t==1)
        {
            seg.apply(l-1,r,F{1});
        }
        else
        {
            cout<<seg.prod(l-1,r).inversion<<endl;
        }
    }
}