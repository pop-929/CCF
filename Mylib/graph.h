#pragma once
#include"stack_and_queue.h"
#include"vector.h"
#include<fstream>


const double MAXCOST = 10000;		//���Ȩ

struct path_data {
	int start, dest;
	double cost;
	operator double()const { return cost; }
};

template<typename T>
class graph {
	struct edgenode {				//�߽�����ݽṹ
		int dest;					//�ߵ��յ��±�
		double cost;				//�ߵ�Ȩ
		operator int() { return dest; }
		edgenode(int d=0,double c=0):dest(d),cost(c){};
	};
	T *DP;							//��������ָ��
	list<edgenode> *HL;				//����������ָ��
	int sizeD, sizeE, maxD;			//��������������������С
	double get_cost(int, int)const;	//��ʼ����յ��±��ȡ�ߵ�Ȩ
	void BFS(int,bool*)const;		//������ȱ���
	void DFS(int,bool*)const;		//������ȱ���
	void build_heap(path_data*, int)const;			//�ѳ���Ϊsize��path_heap�ṹ����Ϊ��
	void percolate_down(path_data*, int, int)const;	//���±�Ϊ[pos,size)��Χ�ڵ�path_data�ṹ����Ԫ�����µ���Ϊ��
public:
	graph(int n=30):sizeD(0),sizeE(0),maxD(n)		//���캯��
		{DP = new T[n];	HL = new list<edgenode>[n];}
	~graph() { delete []DP;	delete []HL; }			//��������
	bool empty_g()const{ return sizeD == 0; }		//�п�
	bool full_g()const { return sizeD == maxD; }	//����
	int sizeD_g()const { return sizeD; }			//ȡ������
	int sizeE_g()const { return sizeE; }			//ȡ����
	double get_cost_g(const T&, const T&)const;		//ͨ���ߵ�ʼ����յ�ȡȨ
	int find_node_g(const T&)const;					//ȡ�����±�
	void BFS_g()const;					//������ȱ���
	void BFS_g(const T&)const;			//����ͨͼ������ȱ���
	void DFS_g()const;					//������ȱ���
	void DFS_g(const T&)const;			//����ͨͼ������ȱ���

	void prim(const T&, path_data*, int)const;		//����ķ�㷨
	bool find_noed_g(T&, int)const;					//���±�Ϊpos�Ķ���浽x��
	int insertD_g(const T&);						//���붥��
	void insertE_g(const T&, const T&, double);		//�����
	void deleteD_g(const T&);						//ɾ������
	void deleteE_g(const T&, const T&);				//ɾ����
	void read_graph_g(const char*);					//�Ӵ����ļ��ж�ȡͼ������
	void write_graph_g(const char*);				//�������ļ�д��ͼ������
	template<typename T>
	friend istream& operator>>(istream&, graph<T>&);//�������뺯��
};



template<typename T>		//��ʼ����յ��±��ȡ�ߵ�Ȩ
double graph<T>::get_cost(int i, int j) const{
	if(i< 0||i >=sizeD||j< 0||j >=sizeD ||i==j)
		{cout<<"λ�ô��󣬲���ʧ�ܣ���get_cost��"<<endl;	return -1;}
	if(!HL[i].empty_l()){
		typename list<edgenode>::const_iterator first=HL[i].begin_l(),last=HL[i].end_l();
		for(;first!=last;++first)
			if(first->dest==j)	return first->cost;
	}	cout<<"���ҵı߲����ڣ�(get_cost)"<<endl;	return -1;
}

template<typename T>		//������ȱ��������ã�
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

template<typename T>		//����ͨͼ������ȱ��������ã�
void graph<T>::BFS_g(const T& x) const {
	if (sizeD == 0)
		{cout << "��ͼ����BFS_g��" << endl;	return;}
	int pos = find_node_g(x);
	if (pos == -1)
		return;
	bool *visited = new bool[sizeD];
	for (int n = 0; n < sizeD; n++)
		visited[n] = 0;
	BFS(pos, visited);
	delete[]visited;
}

template<typename T>		//ȫͼ������ȱ��������ã�
void graph<T>::BFS_g() const {
	if(sizeD==0)
		{cout << "��ͼ����BFS_g��" << endl;	return;}
	bool *visited = new bool[sizeD];
	for (int n = 0; n < sizeD; n++)
		visited[n] = 0;
	for (int pos = 0; pos < sizeD; pos++)
		if (visited[pos] == 0)
			BFS(pos, visited);
	delete[]visited;
}

template<typename T>		//������ȱ���(����)
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

template<typename T>		//����ͨͼ������ȱ���
void graph<T>::DFS_g(const T & x) const{
	if(sizeD==0)
		{cout << "��ͼ����DFS_g��" << endl;	return;}
	int pos=find_node_g(x);
	if(x==-1)
		return;
	bool *visited=new bool[sizeD];
	for(int i=0;i<sizeD;i++)
		visited[i]=0;
	DFS(pos,visited);
	delete[]visited;
}

template<typename T>		//������ȱ���
void graph<T>::DFS_g() const{
	if(sizeD==0)
		{cout << "��ͼ����DFS_g��" << endl;	return;}
	bool *visited=new bool[sizeD];
	for(int i=0;i<sizeD;i++)
		visited[i]=0;
	for(int i=0;i<sizeD;i++)
		if(visited[i]==0)
			DFS(i,visited);
	delete[]visited;
}

template<typename T>		//ͨ���ߵ�ʼ����յ�ȡȨ
double graph<T>::get_cost_g(const T& x1, const T& x2) const
	{return get_cost(find_node_g(x1),find_node_g(x2));}

template<typename T>		//ȡ�����±�
int graph<T>::find_node_g(const T& x) const{
	if(sizeD==0)	return -1;
	for(int i=0;i<sizeD;i++)
		if(DP[i]==x) return i;
	cout<<"�Ҳ����ý�㣡(find_node_g)"<<endl;	
	return -1;
}

template<typename T>		//���±�Ϊpos�Ķ���浽x��
inline bool graph<T>::find_noed_g(T& x, int pos) const{
	if(pos< 0||pos >=sizeD)
		{cout<<"����ʧ�ܣ�λ�÷Ƿ���(find_node_g)"<<endl;	return 0;}
	x=DP[pos];	return 1;
}

template<typename T>		//���붥��
inline int graph<T>::insertD_g(const T& x){
	if(sizeD==maxD)
		{cout<<"ͼ���������ٲ����ˣ�(insertD_g)"<<endl; return 0;}
	DP[sizeD]=x;	++sizeD;
	return sizeD;
}

template<typename T>		//�����
void graph<T>::insertE_g(const T& x1, const T& x2, double w){
	int i=find_node_g(x1),j=find_node_g(x2);
	if(i==-1||j==-1||i==j)return;
	edgenode e(j,w);	HL[i].push_back_l(e);	++sizeE;
}

template<typename T>		//ɾ������
void graph<T>::deleteD_g(const T& x){
	int n=find_node_g(x),m;
	if(-1==n)
		{cout<<"�Ҳ����ý�㣬ɾ��ʧ�ܣ�(deleteD_g)"<<endl;	return;}
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

template<typename T>		//ɾ����
void graph<T>::deleteE_g(const T& x1, const T& x2){
	int i = find_node_g(x1), j = find_node_g(x2);
	if(i<0||j<0||i==j)
		{cout << "����ʧ�ܣ�Ҫɾ���ı߲����ڣ���deleteE_g��" << endl;	return;}
	typename list<edgenode>::iterator first=HL[i].begin_l(), last=HL[i].end_l();
	for(;first!=last;++first)
		if((*first).dest==j)
			{HL[i].erase_l(first);	--sizeE;	break;}
}

template<typename T>		//�Ӵ����ļ��ж�ȡͼ������
void graph<T>::read_graph_g(const char *filename){
	ifstream fin(filename, ios::in);
	if (!fin)
		{cout << "���ļ� " << filename << " ʧ�ܣ�" << endl;	return;}
	fin >> *this;	fin.close();
}

template<typename T>		//�������ļ�д��ͼ������
void graph<T>::write_graph_g(const char *filename){
	ifstream fout(filename, ios::out);
	if(!fout)
		{cout << "���ļ� " << filename << " ʧ�ܣ�" << endl;	return;}
	typename list<edgenode>::const_iterstor first, last;
	for (int i = 0; i < sizeD; i++) {
		fout << i << DP[i] << ':';
		if (HL[i].empty_l())
			fout << "�����ӵ㡣";
		else {
			first = HL[i].begin_l();	last = HL[i].end_l();
			for (; first != last; ++first)
				fout << '(' << (*first).dest << ',' << (*first).cost << ',' << DP[(*first).dest] << ") ";
		}fout << endl;
	}	fout.close();
}

template<typename T>		//�������뺯��
istream & operator>>(istream& istr, graph<T>& g){
	T x1,x2;	int n;	double w;
	cout<<"�����붥�㣺"<<endl;
	while(istr>>x1) g.insertD_g(x1);	cin.clear();
	cout<<"�뽫�������ӣ�"<<endl;
	while(istr>>x1)
		{istr>>x2>>w;	g.insertE_g(x1,x2,w);}
	return istr;
}
