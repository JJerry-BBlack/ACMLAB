namespace fastIO
{
	#ifdef LOCAL
	#define DEBUG
	#endif
	#define BUF_SIZE 100000
	#define DECIMAL 6
	#define LL long long
	static bool IOerror=0;
	#ifdef DEBUG
	inline char nc(){char ch=getchar();if(ch==-1)IOerror=1;return ch;}
	#else
	inline char nc(){static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;if(p1==pend){p1=buf;pend=buf+fread(buf,1,BUF_SIZE,stdin);if(pend==p1){IOerror=1;return -1;}}return *p1++;}
	#endif
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	template<class T> inline bool read(T&x){bool sign=0;char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return false;if(ch=='-')sign=1,ch=nc();for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';if(sign)x=-x;return true;}
	inline bool read(unsigned long long&x){char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return false;for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';return true;}
	inline bool read(unsigned int&x){char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return false;for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';return true;}
	inline bool read(double&x){bool sign=0;char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return false;if(ch=='-')sign=1,ch=nc();for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';if(ch=='.'){double tmp=1;ch=nc();for(;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');}if(sign)x=-x;return true;}
	inline bool read(char*s){char ch=nc();for(;blank(ch);ch=nc());if(IOerror)return false;for(;!blank(ch)&&!IOerror;ch=nc())*s++=ch;*s=0;return true;}
	inline bool read(char&c){for(c=nc();blank(c);c=nc());if(IOerror){c=-1;return false;}return true;}
	inline bool read(std::string&s){s.clear();char ch=nc();for(;blank(ch);ch=nc());if(IOerror)return false;for(;!blank(ch)&&!IOerror;ch=nc())s+=ch;return true;}
	template<class T,class... U> bool read(T&h,U&... t){return read(h)&&read(t...);}
	struct Ostream_fwrite
	{
		#ifdef DEBUG
		inline void out(char ch) { putchar(ch); }
		#else
		char*buf,*p1,*pend;
		Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
		inline void out(char ch){if(p1==pend){fwrite(buf,1,BUF_SIZE,stdout);p1=buf;}*p1++=ch;}
		#endif
		template<class T> inline void print(T x){static char s[41],*s1;s1=s;if(!x)*s1++='0';if(x<0)out('-'),x=-x;while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);}
		inline void print(char ch){out(ch);}
		inline void print(unsigned long long x){static char s[41],*s1;s1=s;if(!x)*s1++='0';while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);}
		inline void print(unsigned int x){static char s[41],*s1;s1=s;if(!x)*s1++='0';while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);}
		inline void print(double x,int y=DECIMAL){static LL mul[]={1,10,100,1000,10000,100000,
				1000000,10000000,100000000,1000000000,
				10000000000LL,100000000000LL,
				1000000000000LL,10000000000000LL,
				100000000000000LL,1000000000000000LL,
				10000000000000000LL,100000000000000000LL};
			if(x<-1e-12)out('-'),x=-x;x*=mul[y];LL x1=(LL)floor(x);if(x-floor(x)>=0.5)++x1;LL x2=x1/mul[y],x3=x1-x2*mul[y];print(x2);if(y>0){out('.');for(size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i);print(x3);}}
		inline void print(char*s){while(*s)out(*s++);}
		inline void print(const char*s){while(*s)out(*s++);}
		inline void print(std::string s){print(s.c_str());}
		#ifndef DEBUG
		inline void flush(){if(p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
		~Ostream_fwrite(){flush();}
		#endif // !DEBUG
	}Ostream;
	template<class T> inline void print(T x){Ostream.print(x);}
	template<class T> inline void println(T x){Ostream.print(x);Ostream.out('\n');}
	inline void print(double x,int y=DECIMAL){Ostream.print(x,y);}
	inline void println(double x,int y=DECIMAL){Ostream.print(x,y);Ostream.out('\n');}
	template<class T,class... U> void print(const T&h,const U&... t){print(h);Ostream.out(' ');print(t...);}
	template<class T,class... U> void println(const T&h,const U&... t){print(h);Ostream.out(' ');println(t...);}
	#ifndef DEBUG
	inline void flush(){Ostream.flush();}
	#endif
	#undef LL
	#undef DECIMAL
	#undef BUF_SIZE
	//本地 getchar/putchar ，提交 fread/fwrite
	//本地支持终端交互输入输出
}
using namespace fastIO;