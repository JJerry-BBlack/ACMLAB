// operation 1: a[i] -> b*a[i]+c
// operation 2: \sum_{l<=i<r} a[i]

struct S
{
    mint a;
    int siz;
};

struct F
{
    mint a,b;
};

S op(S l,S r){return S{l.a+r.a,l.siz+r.siz};}

S e(){return S{0,0};}

S mapping(F l,S r){return S{r.a*l.a+r.siz*l.b,r.siz};}

F composition(F l,F r){return F{r.a*l.a,r.b*l.a+l.b};}

F id(){return F{1,0};}

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<S>a(n);
    for(int i=0;i<n;i++)
    {
        mint x;
        cin>>x;
        a[i]=S{x,1};
    }

    lazy_segtree<S,op,e,F,mapping,composition,id>seg(a);

    for(int i=0;i<q;i++)
    {
        int t,l,r;
        cin>>t>>l>>r;
        if(t==0)
        {
            mint b,c;
            cin>>b>>c;
            seg.apply(l,r,F{b,c});
        }
        else
        {
            cout<<seg.prod(l,r).a<<endl;
        }
    }
}