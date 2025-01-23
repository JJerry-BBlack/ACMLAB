#include<bits/stdc++.h>
using namespace std;

const int N=100005;
int len[2*N+5];

void manacher(string& s)
{
    int siz=s.size();
    string str="#";
    for(int i=0;i<siz;i++)
        str=str+s[i]+"#";
    cout<<str<<'\n';
    siz=str.size();
    for(int i=0,l=0,r=-1;i<siz;i++)
    {
        int k=(i>r)?1:min(len[l+r-i],r-i+1);
        while(0<=i-k&&i+k<siz&&str[i-k]==str[i+k])
        {
            k++;
        }
        len[i]=k--;
        if(i+k>r)
        {
            l=i-k;
            r=i+k;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    
    int n;
    cin>>n;
    string s;
    cin>>s;
    manacher(s);
    for(int i=0;i<2*n+1;i++)
        cout<<len[i]<<" \n"[i==2*n];

    return 0;
}