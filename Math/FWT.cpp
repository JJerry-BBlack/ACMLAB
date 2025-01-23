#include<bits/stdc++.h>
using namespace std;

//is=+1 : fwt
//is=-1 : ifwt

//basically, we need +,-,* for class T
// for xor_fwt and xor_convolution, we need /2 (or change it to *2^(-1) manually)

template <class T>
void and_fwt(T f[],int ldn,int is=1)
{
	int n=(1<<ldn);
	for(int ldm=1;ldm<=ldn;ldm++)
	{
		int m=(1<<ldm),mh=m>>1;
		for(int r=0;r<n;r+=m)
		{
			int t1=r,t2=r+mh;
			for(int j=0;j<mh;j++,t1++,t2++)
			{
				T u=f[t1],v=f[t2];
				if(is>0)f[t1]=u+v,f[t2]=v;
				else f[t1]=u-v,f[t2]=v;
			}
		}
	}
}

template <class T>
void or_fwt(T f[],int ldn,int is=1)
{
	int n=(1<<ldn);
	for(int ldm=1;ldm<=ldn;ldm++)
	{
		int m=(1<<ldm),mh=m>>1;
		for(int r=0;r<n;r+=m)
		{
			int t1=r,t2=r+mh;
			for(int j=0;j<mh;j++,t1++,t2++)
			{
				T u=f[t1],v=f[t2];
				if(is>0)f[t1]=u,f[t2]=u+v;
				else f[t1]=u,f[t2]=v-u;
			}
		}
	}
}

template <class T>
void xor_fwt(T f[],int ldn,int is=1)
{
	int n=(1<<ldn);
	for(int ldm=1;ldm<=ldn;ldm++)
	{
		int m=(1<<ldm),mh=m>>1;
		for(int r=0;r<n;r+=m)
		{
			int t1=r,t2=r+mh;
			for(int j=0;j<mh;j++,t1++,t2++)
			{
				T u=f[t1],v=f[t2];
				if(is>0)f[t1]=u+v,f[t2]=u-v;
				else f[t1]=(u+v)/2,f[t2]=(u-v)/2;
			}
		}
	}
}

// will **change** f[] and g[], result is stored in f[]
template <class T>
void and_convolution(T f[],T g[],int n)
{
	int ldn=__lg(n);assert((1<<ldn)==n);
	and_fwt(f,ldn);and_fwt(g,ldn);
	for(int i=0;i<n;i++)f[i]=f[i]*g[i];
	and_fwt(f,ldn,-1);
}

template <class T>
void or_convolution(T f[],T g[],int n)
{
	int ldn=__lg(n);assert((1<<ldn)==n);
	or_fwt(f,ldn);or_fwt(g,ldn);
	for(int i=0;i<n;i++)f[i]=f[i]*g[i];
	or_fwt(f,ldn,-1);
}

template <class T>
void xor_convolution(T f[],T g[],int n)
{
	int ldn=__lg(n);assert((1<<ldn)==n);
	xor_fwt(f,ldn);xor_fwt(g,ldn);
	for(int i=0;i<n;i++)f[i]=f[i]*g[i];
	xor_fwt(f,ldn,-1);
}