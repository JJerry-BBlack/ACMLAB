struct Hopcroft_Karp
{
	vector<vector<int>>es;
	vector<int>d,match;
	vector<bool>used,used2;
	const int n,m;
	Hopcroft_Karp(int n,int m):es(n),d(n),match(m),used(n),used2(n),n(n),m(m){}
	void add_edge(int u,int v){es[u].push_back(v);}
	void _bfs()
	{
		fill(begin(d),end(d),-1);
		queue<int>que;
		for(int i=0;i<n;i++)
		{
			if (!used[i]){que.push(i);d[i] = 0;}
		}
		while (!que.empty())
		{
			int i=que.front();
			que.pop();
			for(auto &e:es[i])
			{
				int j=match[e];
				if(j!=-1&&d[j]==-1){que.push(j);d[j]=d[i]+1;}
			}
		}
	}
	bool _dfs(int now)
	{
		used2[now]=true;
		for (auto &e:es[now])
		{
			int u=match[e];
			if(u==-1||(!used2[u]&&d[u]==d[now]+1&& _dfs(u)))
			{
				match[e]=now,used[now]=true;
				return true;
			}
		}
		return false;
	}
	int max_matching() // 右边的i与左边的match[i]匹配。
	{
		fill(begin(match),end(match),-1);
		fill(begin(used),end(used),false);
		int ret=0;
		while(1)
		{
			_bfs();
			fill(begin(used2),end(used2),false);
			int flow=0;
			for(int i=0;i<n;i++){if(!used[i]&&_dfs(i))flow++;}
			if(flow==0)break;
			ret+=flow;
		}
		return ret;
	}
};

string s[305];
int x[305][305],y[305][305];

void solve()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>s[i];
	int l=0,r=0;
	memset(x,-1,sizeof(x));
	memset(y,-1,sizeof(y));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='#')continue;
			x[i][j]=l;
			while(j+1<m&&s[i][j+1]=='.'){x[i][j+1]=l;j++;}
			l++;
		}
	}
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<n;i++)
		{
			if(s[i][j]=='#')continue;
			y[i][j]=r;
			while(i+1<n&&s[i+1][j]=='.'){y[i+1][j]=r;i++;}
			r++;
		}
	}
	if(l==0&&r==0)
	{
		cout<<0;
		return;
	}
	Hopcroft_Karp BM(l,r);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(x[i][j]!=-1&&y[i][j]!=-1)BM.add_edge(x[i][j],y[i][j]);
		}
	}
	cout<<BM.max_matching();
}