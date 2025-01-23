struct MCFF{ // Maximum cost feasible flow 最大费用可行流
	int n, s, t, cost, dis[N], st[N], vis[N];
	int head[N], nxt[M], v[M], w[M], flow[M], ecnt;
	
	inline void ade(int a, int b, int c, int dis){ v[++ecnt]=b; nxt[ecnt]=head[a]; w[ecnt]=dis; flow[ecnt]=c; head[a]=ecnt;}
	
	inline void addedge(int a, int b, int c, int dis){ ade(a,b,c,dis); ade(b,a,0,-dis);}
	
	inline void init(int _n, int _s, int _t){
		n=_n; s=_s; t=_t; ecnt=1; cost=0;
		memset(head, 0, sizeof head);
	}
	
	inline int spfa(){
		queue<int> q; q.push(s);
		memset(st,0,sizeof st);
		memset(dis,0x3f,sizeof dis); dis[s]=0;
		while(q.size()){
			int u=q.front(); q.pop(); vis[u]=0;
			for(int i=head[u];i;i=nxt[i]){
				if(flow[i] and dis[v[i]]>dis[u]+w[i]){
					dis[v[i]]=dis[u]+w[i];
					if(!vis[v[i]]) q.push(v[i]), vis[v[i]]=1;
				}
			}
		} return dis[t]<0;
	}
	
	int dfs(int x, int f){
		if(x==t) return cost+=dis[t]*f,f;
		st[x]=1; int fl=0;
		for(int i=head[x];f and i;i=nxt[i]){
			if(flow[i] and !st[v[i]] and dis[v[i]]==dis[x]+w[i]){
				int mi=dfs(v[i], min(f, flow[i]));
				flow[i]-=mi; flow[i^1]+=mi; fl+=mi; f-=mi;
			}
		} return fl;
	}
	
	inline int work(){
		while(spfa()) dfs(s, INF);
		return cost;
	}
}f;