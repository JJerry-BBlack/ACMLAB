struct node
{
	string name;
	int cnt;
	node(){}
	node(string s,int c){name=s,cnt=c;}
	bool operator<(const node& a)const // 结构体排序
	{
		if(cnt!=a.cnt)
		return cnt>a.cnt;// 先按数量从大到小
		if(name.size()!=a.name.size())
		return name.size()>a.name.size(); // 再按标签长度从小到大
		return name<a.name; // 最后按字典序，string可以直接进行对比
	}
};