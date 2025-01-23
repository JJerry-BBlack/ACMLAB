int LOG[2000005];
void init()
{
    LOG[0]=-1;
    for(int i=1;i<=2000000;i++)
        LOG[i]=LOG[i/2]+1;
}

template<typename T,int N,int K,T(*F)(T&,T&)>
struct Sparse_Table
{
    T st[K][N];
    template<typename Iterator>
    void build(Iterator bg,Iterator ed)
    {
        int now=0;
        for(auto i=bg;i!=ed;i++) // 下标从 1 开始
        {
            st[0][++now]=(*i);
        }
        for(int k=1;k<K;k++)
        {
            for(int i=1;i+(1<<k)-1<=now;i++)
            {
                st[k][i]=F(st[k-1][i],st[k-1][i+(1<<(k-1))]);
            }
        }
    }
    T query(int l,int r)
    {
        int k=LOG[r-l+1];
        return F(st[k][l],st[k][r-(1<<k)+1]);
    }
    // 记得 init !!!
};

int Max(int &a,int &b)
{
    if(a>=b)return a;
    return b;
}

Sparse_Table<int,2000005,25,Max>st; // [](int &a,int &b){return max(a,b);}

void solve()
{
    init();
    vector<int>a(20);
    for(int i=0;i<20;i++)a[i]=i+1;
    st.build(a.begin(),a.end()); // st.build(a+1,a+n+1);
    cout<<st.query(3,10)<<endl;
}