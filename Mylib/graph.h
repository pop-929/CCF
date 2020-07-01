#pragma once
#include"stack_and_queue.h"
#include"vector.h"
#include<fstream>


const double MAXCOST = 10000;		//最大权

struct path_data {
	int start, dest;
	double cost;
	operator double()const { return cost; }
};

template<typename T>
class graph {
	struct edgenode {				//边界点数据结构
		int dest;					//边的终点下标
		double cost;				//边的权
		operator int() { return dest; }
		edgenode(int d=0,double c=0):dest(d),cost(c){};
	};
	T *DP;							//顶点数组指针
	list<edgenode> *HL;				//边链表数组指针
	int sizeD, sizeE, maxD;			//顶点数、边数、容器大小
	double get_cost(int, int)const;	//按始点和终点下标读取边的权
	void BFS(int,bool*)const;		//广度优先遍历
	void DFS(int,bool*)const;		//深度优先遍历
	void build_heap(path_data*, int)const;			//把长度为size的path_heap结构调整为堆
	void percolate_down(path_data*, int, int)const;	//将下标为[pos,size)范围内的path_data结构数组元素向下调整为堆
public:
	graph(int n=30):sizeD(0),sizeE(0),maxD(n)		//构造函数
		{DP = new T[n];	HL = new list<edgenode>[n];}
	~graph() { delete []DP;	delete []HL; }			//析构函数
	bool empty_g()const{ return sizeD == 0; }		//判空
	bool full_g()const { return sizeD == maxD; }	//判满
	int sizeD_g()const { return sizeD; }			//取顶点数
	int sizeE_g()const { return sizeE; }			//取边数
	double get_cost_g(const T&, const T&)const;		//通过边的始点和终点取权
	int find_node_g(const T&)const;					//取顶点下标
	void BFS_g()const;					//广度优先遍历
	void BFS_g(const T&)const;			//弱连通图广度优先遍历
	void DFS_g()const;					//深度优先遍历
	void DFS_g(const T&)const;			//弱连通图深度优先遍历

	void prim(const T&, path_data*, int)const;		//普里姆算法
	bool find_noed_g(T&, int)const;					//将下标为pos的顶点存到x中
	int insertD_g(const T&);						//插入顶点
	void insertE_g(const T&, const T&, double);		//插入边
	void deleteD_g(const T&);						//删除顶点
	void deleteE_g(const T&, const T&);				//删除边
	void read_graph_g(const char*);					//从磁盘文件中读取图的数据
	void write_graph_g(const char*);				//往磁盘文件写入图的数据
	template<typename T>
	friend istream& operator>>(istream&, graph<T>&);//重载输入函数
};



template<typename T>		//按始点和终点下标读取边的权
double graph<T>::get_cost(int i, int j) const{
	if(i< 0||i >=sizeD||j< 0||j >=sizeD ||i==j)
		{cout<<"位置错误，操作失败！（get_cost）"<<endl;	return -1;}
	if(!HL[i].empty_l()){
		typename list<edgenode>::const_iterator first=HL[i].begin_l(),last=HL[i].end_l();
		for(;first!=last;++first)
			if(first->dest==j)	return first->cost;
	}	cout<<"查找的边不存在！(get_cost)"<<endl;	return -1;
}

template<typename T>		//广度优先遍历（内置）
void graph<T>::BFS(int pos,bool* visited) const{
	queue<int> q;	q.push_q(pos);	visited[pos] = 1;	int n;
	typename list<edgenode>::const_iterstor first, last;
	while (!q.empty_q()) {
		pos = q.pop_q();	cout << DP[pos] << ' ';
		if (!HL[pos].empty_l()) {
			first = HL[pos].begin_l();	last = HL[pos].end_l();
			for (; first != last; ++first) {
				n = (*first).dest;
				if (visited[n] == 0)
					{q.push_q(n);	visited[n] = 1;}
			}
		}
	}
}

template<typename T>		//弱连通图广度优先遍历（外用）
void graph<T>::BFS_g(const T& x) const {
	if (sizeD == 0)
		{cout << "空图！（BFS_g）" << endl;	return;}
	int pos = find_node_g(x);
	if (pos == -1)
		return;
	bool *visited = new bool[sizeD];
	for (int n = 0; n < sizeD; n++)
		visited[n] = 0;
	BFS(pos, visited);
	delete[]visited;
}

template<typename T>		//全图广度优先遍历（外用）
void graph<T>::BFS_g() const {
	if(sizeD==0)
		{cout << "空图！（BFS_g）" << endl;	return;}
	bool *visited = new bool[sizeD];
	for (int n = 0; n < sizeD; n++)
		visited[n] = 0;
	for (int pos = 0; pos < sizeD; pos++)
		if (visited[pos] == 0)
			BFS(pos, visited);
	delete[]visited;
}

template<typename T>		//深度优先遍历(内置)
void graph<T>::DFS(int pos,bool *visited) const{
	stack<int> s;	s.push_s(pos);	visited[pos]=1;	int n;
	typename list<edgenode>::const_iterator first,last;
	while (!s.empty_s()) {
		pos = s.pop_s();	cout << DP[pos] << ' ';
		if (!HL[pos].empty_l()) {
			first = HL[pos].begin_l();	last = HL[pos].end_l();
			for (; first != last; ++first) {
				n = (*first).dest;
				if (visited[n] == 0)
					{s.push_s(n);	visited[n] = 1;}
			}
		}
	}
}

template<typename T>		//弱连通图深度优先遍历
void graph<T>::DFS_g(const T & x) const{
	if(sizeD==0)
		{cout << "空图！（DFS_g）" << endl;	return;}
	int pos=find_node_g(x);
	if(x==-1)
		return;
	bool *visited=new bool[sizeD];
	for(int i=0;i<sizeD;i++)
		visited[i]=0;
	DFS(pos,visited);
	delete[]visited;
}

template<typename T>		//深度优先遍历
void graph<T>::DFS_g() const{
	if(sizeD==0)
		{cout << "空图！（DFS_g）" << endl;	return;}
	bool *visited=new bool[sizeD];
	for(int i=0;i<sizeD;i++)
		visited[i]=0;
	for(int i=0;i<sizeD;i++)
		if(visited[i]==0)
			DFS(i,visited);
	delete[]visited;
}

template<typename T>		//通过边的始点和终点取权
double graph<T>::get_cost_g(const T& x1, const T& x2) const
	{return get_cost(find_node_g(x1),find_node_g(x2));}

template<typename T>		//取顶点下标
int graph<T>::find_node_g(const T& x) const{
	if(sizeD==0)	return -1;
	for(int i=0;i<sizeD;i++)
		if(DP[i]==x) return i;
	cout<<"找不到该结点！(find_node_g)"<<endl;	
	return -1;
}

template<typename T>		//将下标为pos的顶点存到x中
inline bool graph<T>::find_noed_g(T& x, int pos) const{
	if(pos< 0||pos >=sizeD)
		{cout<<"操作失败：位置非法！(find_node_g)"<<endl;	return 0;}
	x=DP[pos];	return 1;
}

template<typename T>		//插入顶点
inline int graph<T>::insertD_g(const T& x){
	if(sizeD==maxD)
		{cout<<"图已满不能再插入了！(insertD_g)"<<endl; return 0;}
	DP[sizeD]=x;	++sizeD;
	return sizeD;
}

template<typename T>		//插入边
void graph<T>::insertE_g(const T& x1, const T& x2, double w){
	int i=find_node_g(x1),j=find_node_g(x2);
	if(i==-1||j==-1||i==j)return;
	edgenode e(j,w);	HL[i].push_back_l(e);	++sizeE;
}

template<typename T>		//删除顶点
void graph<T>::deleteD_g(const T& x){
	int n=find_node_g(x),m;
	if(-1==n)
		{cout<<"找不到该结点，删除失败！(deleteD_g)"<<endl;	return;}
	m=HL[n].size_l();	HL[n].clear_l();	sizeE-=m;
	DP[n]=DP[sizeD-1];	--sizeD;
	typename list<edgenode>::iterator first,last;
	for (int i = 0; i < sizeD; i++) 
		if (!HL[i].empty_l()) {
			first = HL[i].begin_l();	last = HL[i].end_l();	m = 0;
			for (; first != last; ++first) {
				if ((*first).dest == n)
					{HL[i].erase_l(first);	if (m)	break;	++m;}
				if ((*first).dest == sizeD)
					{(*first).dest = n;	if (m)	break;	++m;}
			}
		}
}

template<typename T>		//删除边
void graph<T>::deleteE_g(const T& x1, const T& x2){
	int i = find_node_g(x1), j = find_node_g(x2);
	if(i<0||j<0||i==j)
		{cout << "操作失败：要删除的边不存在！（deleteE_g）" << endl;	return;}
	typename list<edgenode>::iterator first=HL[i].begin_l(), last=HL[i].end_l();
	for(;first!=last;++first)
		if((*first).dest==j)
			{HL[i].erase_l(first);	--sizeE;	break;}
}

template<typename T>		//从磁盘文件中读取图的数据
void graph<T>::read_graph_g(const char *filename){
	ifstream fin(filename, ios::in);
	if (!fin)
		{cout << "打开文件 " << filename << " 失败！" << endl;	return;}
	fin >> *this;	fin.close();
}

template<typename T>		//往磁盘文件写入图的数据
void graph<T>::write_graph_g(const char *filename){
	ifstream fout(filename, ios::out);
	if(!fout)
		{cout << "打开文件 " << filename << " 失败！" << endl;	return;}
	typename list<edgenode>::const_iterstor first, last;
	for (int i = 0; i < sizeD; i++) {
		fout << i << DP[i] << ':';
		if (HL[i].empty_l())
			fout << "无连接点。";
		else {
			first = HL[i].begin_l();	last = HL[i].end_l();
			for (; first != last; ++first)
				fout << '(' << (*first).dest << ',' << (*first).cost << ',' << DP[(*first).dest] << ") ";
		}fout << endl;
	}	fout.close();
}

template<typename T>		//重载输入函数
istream & operator>>(istream& istr, graph<T>& g){
	T x1,x2;	int n;	double w;
	cout<<"请输入顶点："<<endl;
	while(istr>>x1) g.insertD_g(x1);	cin.clear();
	cout<<"请将顶点连接："<<endl;
	while(istr>>x1)
		{istr>>x2>>w;	g.insertE_g(x1,x2,w);}
	return istr;
}
