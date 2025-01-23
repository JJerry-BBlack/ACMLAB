//向上取整
for(int l=1;l<=n;l++)
{
	int k=(n+l-1)/l;
	int r=(n-1)/(k-1);
	solve();
	l=r;
}