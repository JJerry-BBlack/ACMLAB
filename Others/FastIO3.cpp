void read(int& x)
{
	char c = getchar(); x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x * 10 + c - 48, c = getchar();
}
inline int read()
{
	int s=0,w=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
	if(ch=='-')w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())
	s=(s<<1)+(s<<3)+(ch^48);
	return (w==-1?-s:s);
}
inline void print(int x) {
	if (x == 0){printf("0\n");return;}
	int num = 0; char c[15];
	while (x) c[++num] = (x % 10) + 48, x /= 10;
	while (num) putchar(c[num--]);
	putchar('\n');
}