template<typename T>
struct matrix
{
    int siz;
    vector<vector<T>>a;
    matrix(int _siz)
    {
        siz=_siz;
        a=vector(siz,vector<T>(siz));
    }
    void resize(int _siz)
    {
        siz=_siz;
        a=vector(siz,vector<T>(siz));
    }
    vector<T>& operator[](int x)
    {
        assert(x>=0&&x<siz);
        return a[x];
    }
    matrix<T> operator*(matrix<T>&b)
    {
        assert(siz==b.siz);
        matrix<T> res(siz);
        for(int i=0;i<siz;i++)
        {
            for(int j=0;j<siz;j++)
            {
                for(int k=0;k<siz;k++)
                {
                    res[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
        return res;
    }
    friend matrix<T> operator^(matrix<T> a,int n)
    {
        matrix<T> res(a.siz);
        for(int i=0;i<a.siz;i++)res[i][i]=1;
        while(n)
        {
            if(n&1)res=res*a;
            a=a*a;n>>=1;
        }
        return res;
    }
};