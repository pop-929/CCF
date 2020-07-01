#pragma once
#include<fstream>
#include"stack_and_queue.h"
#include"vector.h"

template<class T>
class btree{
	struct btnode {
		T data;		btnode *left, *right;
		btnode(const T& x = T(), btnode *l = NULL, btnode *r = NULL) :data(x), left(l), right(r) {}
	};
	btnode *root;			//二叉树根结点
	int size;				//结点个数
	void init_bt() { size = 0;	root = new btnode; }
public:
	btree() :root(NULL) { init_bt(); };						//默认构造函数，生成空树，根无数据
	btree(const btree<T>& bt) { init_bt(); operator=(bt); }	//复制构造函数
	~btree() { clear_bt(); delete root; }					//析构树

	bool empty_bt()const{ return size == 0; }	//判空
	int size_bt()const  { return size; }		//取结点数
	int depth_bt()const;						//求树深
	void print_bt(int)const;					//垂直输出二叉树
	void traversal_preorder_bt()const;			//前序遍历
	void traversal_inorder_bt()const;			//中序遍历
	void traversal_postorder_bt()const;			//后序遍历
	void level_bt()const;						//层次遍历

	void make_bt();						//制造自定义二叉树
	void make_complete_bt();			//快速创建完全二叉树
	void make_pre_and_ino_bt(const T*, const T*,int);		//由前序和中序序列创建二叉树
	void make_post_and_ino_bt(const T*, const T*,int);		//由后序和中序序列创建二叉树	
	void make_complete_bt(const char*);			//从文件中读取并创建完全二叉树（脑残才用）
	btnode *vec_to_link_bt(const vector<T>&);	//将二叉树顺序存储结构转化为链式存储
	const btree& operator=(const btree&);		//复制赋值运算符
	void write_bt(const char*);					//将二叉树写入文件
	
	btnode begin_bt() { return root->left; }			//取首数据指针
	btnode begin_bt()const	{ return root->left; }		//取const型首数据指针
	const T& front_bt()const{ return *begin_bt(); }		//返回const型首元素引用	
	T& front_bt() { return *begin_bt(); }				//返回首元素引用
	void clear_bt();						//清表
	btnode *find_bt(const T&);				//查找某元素并返回指针
	void find_path_bt(const T&)const;		//查找某元素并输出其最短路径
};


template<class T>		//求树深
int btree<T>::depth_bt()const{
	if (!root)			//空树深度为0
		return 0;
	int depth = 0, i;			//深度和每层的结点个数
	queue<btnode*> q;	btnode *temp;	temp = root;	q.push_q(temp);
	while (!q.empty_q()){
		i = q.size_q();			//每层的结点个数等于队列里数据的个数
		depth++;	
		while (i--)	{
			temp = q.pop_q();	//更换结点
			if (temp->left)		q.push_q(temp->left);		//左子树入队
			if (temp->right)	q.push_q(temp->right);		//右子树入队
		}
	}	return depth;
}

template<class T>		//制造自定义二叉树
void btree<T>::make_bt(){
	int floor = 1, lorr = 0, sum = 1, sum_now = 0, num = 0;	// lorr:树的左右孩子（lorr%2==0是右孩子，否则是左孩子）.
				// floor:树的当前深度. sum:上一层非空结点的个数. num:上一层结点的编号. sum_now：当前层的非空结点个数.
	btnode *p=new btnode, *child;		//当前结点和创建根结点
	cout << '\n' << "正在使用make_bt创建自定义二叉树。" << '\n' 
	 	 << "1、Y创建数据结点；0、N设置空节点；5、C查看结点个数；9结束输入。 " 
		 << '\n' << "第 0 层:" << '\n' << "请输入根结点数据：";
	cin >> root->data;	size++;		cout << '\n' << "第 1 层:" << endl;
	queue<btnode*> q;	q.push_q(root);				//根结点队伍
	while (!q.empty_q() || lorr % 2 == 1){
		++lorr;
		if (lorr % 2 == 1)
			{++num;	p = q.pop_q();}		//左儿子，编号加一，换一个爸爸 //爸爸出山
		if (num > sum){					//如果编号大于节点数，就跑到下一层
			sum = sum_now; floor++; num = 1; sum_now = 0;		//初始化各个数据
			cout << '\n' << "第 " << floor << " 层：" << endl;
		}
		if (lorr % 2 == 1)	cout << "当前为左儿子，";
		else  cout << "当前为右儿子，";
		char leaf_flag;					//是否创立结点
	here0:
		cout << "爸爸是( " << p->data << " )  创建非空结点？（1/0/9）：";
	here1:
		cin >> leaf_flag;
		switch (leaf_flag){
			//空结点（什么都不用做，反正本来都是NULL）
		case '0':	case 'n':	case 'N':	 break;
			//非空结点
		case '1':	case 'y':	case 'Y':
			child = new btnode;			//创建子树（结点）		
			cout << "请输入数据：";
			cin >> child->data;							//输入数据			
			if (lorr % 2 == 1)							//余数为1说明是左孩子
				p->left = child;						//父节点左指针指向该子树						
			else
				p->right = child;						//父节点右指针指向该子树	
			q.push_q(child);							//结点入队成长
			++sum_now;	size++; 	break;				//当前层数数据节点个数加1			
			//查看当前结点个数
		case '5':	case 'c':	case 'C':	cout << "当前结点个数：" << size << endl;	goto here0;		break;
			//结束输入
		case '9':	q.~queue();	return;
			//错误的输入
		default:	cout << "输入错误，请从新输入："; goto here1;	break;
		}
	}
}

template<class T>		//快速创建完全二叉树
void btree<T>::make_complete_bt(){
	int lorr = 0;				// 树的左右孩子（lorr%2==1是左孩子，否则是右孩子）.
	queue<btnode*> q;	T temp;	btnode *p, *child;	p = root;	
	cout << "正在使用快速建立完全二叉树。" << '\n' << "请输入二叉树，按照层次的顺序输入，EOF结束：" << endl;
	cin >> temp;	root->data = temp;	q.push_q(root);
	while (cin >> temp){		//直到遇到EOF才结束(ctrl+z和回车)
		++lorr;	child = new btnode;	child->data = temp;
		if (lorr % 2 == 1)
			{p = q.pop_q();	p->left = child;}		//爸爸出山,认左儿子
		else
			p->right = child;	//认右儿子
		++size;	q.push_q(child);
	}	cin.clear();	//重置流的状态，使之有效
}

template<class T>		//将二叉树顺序存储结构转化为链式存储
typename btree<T>::btnode * btree<T>::vec_to_link_bt(const vector<T>& l)
{//入队时还是个孩子，出来的时候就变成了爸爸
	int n = l.get_size_v(), i = 0;
	if (n == 0)
		return NULL;
	queue<btnode*> q;	btnode *parent, *child;
	root(l[0]);		q.push_q(root);
	while (!q.empty_q()){
		parent = q.pop_q();
		if (i * 2 + 1 < n&&l[i * 2 + 1] != T()){
			child = new btnode(l[i * 2 + 1]);
			parent->left = child;	q.push_q(child);
		}
		if (i * 2 + 2 < n&&l[i * 2 + 2] != T()){
			child = new btnode(l[i * 2 + 2]);
			parent->right = child;	q.push_q(child);
		}	i++;
		while (i < n&&l[i] == T())	i++;
	}	return root;	
}

template<class T>		//从文件中读取并创建完全二叉树(垃圾设计)
void btree<T>::make_complete_bt(const char* filename){
	ifstream fin(filename, ios::in);			//打开文件		之后和快速创建完全二叉树一样
	if (!fin)
		{cout << "打开文件 " << filename << " 失败！" << endl;	return;}
	int lorr = 0;	queue<btnode*> q;			// 树的左右孩子（lorr%2==1是左孩子，否则是右孩子）.

	btnode *p, *child = new btnode;	p = root;
	fin >> root->data;	q.push_q(root);		++size;
	while (!fin.eof()) {			//到文件底结束	
		++lorr;		child = new btnode;
		fin >> child->data;
		if (lorr % 2 == 1)
			{p = q.pop_q();	p->left = child;}	//爸爸出山,认左儿子			
		else
			p->right = child;	//认右儿子
		size++;		q.push_q(child);
	}
	if (p->left == child)
		p->left = NULL;
	if (p->right == child)
		p->right = NULL;
	delete child;	--size;	fin.close();
}

template<class T>		//将二叉树写入文件
void btree<T>::write_bt(const char* filename){
	ofstream fout(filename, ios::out);				//打开文件		之后和快速创建完全二叉树一样
	if (!fout)
		{cout << "打开文件 " << filename << " 失败！" << endl;	return;}
	if (!root)					//空树
		return;
	int depth = 0, i, n = 1;			//深度和每层的结点个数
	queue<btnode*> q;	btnode *temp;	temp = root;	q.push_q(temp);
	fout << "-----第 0 层-----：" << '\n' << root->data << "  ";
	while (n != size){
		i = q.size_q();		depth++;	//每层的结点个数等于队列里数据的个数
		
		fout << '\n' << "-----第 " << depth << " 层-----：" << '\n';
		while (i--){		
			temp = q.pop_q();	//更换结点
			if (temp->left) { 	//左子树入队			 
				q.push_q(temp->left);	++n;
				fout << "左子树：" << temp->left->data << " -->父节点：" << temp->data << endl;
			}
			if (temp->right) {	//右子树入队			
				q.push_q(temp->right);	++n;
				fout << "右子树：" << temp->right->data << " -->父节点：" << temp->data << endl;
			}
		}
	}	fout.close();	
}

template<class T>		//由前序和中序序列创建二叉树
void btree<T>::make_pre_and_ino_bt(const T *pre, const T *ino, int n)
{/* bt为左子树：（在中序序列中bt在父节点左边：i_site<fi_site）
		1、右子树长度：父节点中序下标-bt中序下标-1：	fi_site-i_site-1。
		2、左子树长度：树总长-右子树长度-1：			leng-r_num-1。
	bt为右子树：（在中序序列中bt在父节点右边：i_site>fi_site）
		1、左子树长度：bt中序下标-父节点中序下标-1：	i_site-fi_site-1。
		2、右子树长度：树总长-左子树长度-1：			leng-l_num-1。
	左孩子下标：bt前序下标+1：				p_site+1。
	右孩子下标：bt前序下标+左子树长度+1：	p_site+l_num+1。*/
	stack<btnode*> s;	stack<int> p, i, l, fi;	//数据栈,前、中序下标栈。树长栈。父结点中序下标栈
	int p_site, i_site = 0, fi_site = n;			//前、中序下标。父结点中序下标
	int leng = n, old_leng = 0, l_num, r_num, x;	//树长。上一树长。左、右子树长。
	btnode *bt, *child;	root->data = pre[0];	++size;	//当前结点。孩子结点	
	for (x = 0; x < n; x++)
		if (root->data == ino[x])	break;
	s.push_s(root);		l.push_s(n);	p.push_s(0);	i.push_s(x);
	while (size != n){
		bt = s.pop_s();		leng = l.pop_s();		//当前结点、树长更新
		p_site = p.pop_s();	i_site = i.pop_s();		//当前结点前、中序下标更新
		if (leng == 1) {			//如果是叶子结点，直接进行下一轮循环		
			fi_site = fi.pop_s();	//上寻到上一个有右子树的树的父结点的中序下标
			old_leng = 1;	continue;			//叶子结点的标志		
		}
		if (i_site < fi_site)		//若bt是左子树（中序里左子树在父节点左边），则左右子树长度的关系(起始的根结点默认为左子树)
			{r_num = fi_site - i_site - 1;	l_num = leng - r_num - 1;}
		else 						//bt是右子树的子树长度计算方法与bt为左子树不一样
			{l_num = i_site - fi_site - 1;	r_num = leng - l_num - 1;}
		child = new btnode;			++size;		//新建左孩子结点
		if (l_num > 0 && old_leng != 1) {				//如果该树bt有左子树且上一树不是叶子		
			if (r_num > 0) {			//如果有右子树，需要将当前结点的信息保存下来			
				s.push_s(bt);	l.push_s(leng);		fi.push_s(fi_site);
				p.push_s(p_site);	i.push_s(i_site);
			}
			child->data = pre[p_site + 1];
			bt->left = child;	l.push_s(l_num);		//认儿子。左子树长度压入栈。
			for (x = i_site - l_num; x < i_site; x++)	//当前结点-左子树长度为起始点，搜索到当前结点
				if (child->data == ino[x])	break;
			s.push_s(child);	p.push_s(p_site + 1);	i.push_s(x);	//左孩子，左孩子前、中序下标压入栈
		}
		else {
			child->data = pre[p_site + l_num + 1];
			bt->right = child;	l.push_s(r_num);
			for (x = i_site + 1; x < fi_site; x++)		//当前结点+1为起始点，向后搜索到父节点的位置
				if (child->data == ino[x])	break;
			s.push_s(child);	p.push_s(p_site + l_num + 1);	i.push_s(x);	//繁琐的压栈			
		}	fi_site = i_site;	old_leng = leng;	
	}
}

template<class T>		//由后序和中序序列创建二叉树
void btree<T>::make_post_and_ino_bt(const T *post, const T *ino, int n)
{/*	左孩子下标：bt后序下标-右子树长度-1：p_site-r_num-1。
	右孩子下标：bt后序下标-1：p_site-1。 */
	stack<btnode*> s;	stack<int> p, i, l, fi;	//后、中序下标栈。树长栈。父结点中序下标栈
	int p_site, i_site = 0, fi_site = n;			//后、中序下标。父结点中序下标
	int leng = n, old_leng = 0, l_num, r_num, x;	//树长。上一树长。左、右子树长。
	btnode *bt, *child;		root->data = post[n - 1];	++size;
	for (x = 0; x < n; x++)
		if (root->data == ino[x])	break;
	s.push_s(root);		l.push_s(n);	p.push_s(n - 1);	i.push_s(x);
	while (size != n){
		bt = s.pop_s();		leng = l.pop_s();
		p_site = p.pop_s();	i_site = i.pop_s();
		if (leng == 1)
			{fi_site = fi.pop_s();	old_leng = 1;	continue;}
		if (i_site < fi_site)
			{r_num = fi_site - i_site - 1;	l_num = leng - r_num - 1;}
		else 
			{l_num = i_site - fi_site - 1;	r_num = leng - l_num - 1;}
		child = new btnode;		++size;
		if (l_num > 0 && old_leng != 1){
			if (r_num > 0){
				s.push_s(bt);	l.push_s(leng);		fi.push_s(fi_site);
				p.push_s(p_site);	i.push_s(i_site);
			}
			child->data = post[p_site - r_num - 1];			//左孩子下标：bt后序下标-右子树长度-1：p_site-r_num-1。			
			bt->left = child;	s.push_s(child);
			for (x = i_site - l_num; x < i_site; x++)		//从现在位置的前左子树个位置开始，向后搜索到现在的位置
				if (child->data == ino[x])	break;
			l.push_s(l_num);	p.push_s(p_site - r_num - 1);	i.push_s(x);
		}
		else {
			child->data = post[p_site - 1];					//右孩子下标：bt后序下标 - 1：p_site - 1。
			bt->right = child;	s.push_s(child);
			for (x = i_site + 1; x < fi_site; x++)			//从当前位置+1开始，向后搜索到父节点的位置
				if (child->data == ino[x])	break;
			l.push_s(r_num);	p.push_s(p_site - 1);	i.push_s(x);
		}	fi_site = i_site;	old_leng = leng;		
	}
}


struct location { int xindent, ylevel; };		//结点坐标位置
void gotoxy(int x, int y) {			//输出位置
	static int level = 0, indent = 0;
	if (y == 0)						//重新输出二叉树时要重新赋值
		{indent = 0; level = 0;}
	if (level != y)					//若层数增加，则缩进量从0开始
		{cout << endl;	indent = 0; level++;}
	cout.width(x - indent);			//根据已有缩进量确定当前缩进量
	indent = x;						//记录当前缩进量
}
template<class T>		//垂直输出二叉树
void btree<T>::print_bt(int screenwidth)const{
	if (root == NULL)
		return;
	const btnode *roott; roott = root;
	int level = 0, offset = screenwidth / 2;			//从0层开始，缩进量是屏幕宽度的一半
	location floc, cloc;								//记录双亲和孩子结点的输出位置的变量
	queue<const btnode*> q;								//储存结点指针的队列
	queue<location> lq;									//储存结点输出位置的队列
	floc.xindent = offset;	floc.ylevel = level;		//根结点输出位置
	q.push_q(roott);	lq.push_q(floc);				//根指针入队//根结点位置数据入队				
	while (!q.empty_q()){
		roott = q.pop_q();	floc = lq.pop_q();
		gotoxy(floc.xindent, floc.ylevel);				//确定输出光标位置
		cout << roott->data;							//输出结点
		if (floc.ylevel != level)						//层数加1，缩进量减半
			{level++; offset = offset / 2;}
		if (roott->left) {			//如果有左孩子		
			q.push_q(roott->left);	cloc.ylevel = floc.ylevel + 1;				//计算左孩子输出位置
			cloc.xindent = floc.xindent - offset / 2;	lq.push_q(cloc);		//左孩子输出位置入队
		}
		if (roott->right){
			q.push_q(roott->right);	cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent + offset / 2;	lq.push_q(cloc);
		}
	}	cout << endl;	
}


template<class T>		//前序遍历
void btree<T>::traversal_preorder_bt()const
{/*以t指向的结点是否存在为中心，判断根结点是否为最左子树。
 如果存在，则根结点不是最左子树，需要存入右子树；不存在则根为最左子树，需要进行进一步的操作*/
	if (root == NULL)
		return;
	stack<const btnode*> s;
	const btnode *roott;	roott = root;
	while (roott || !s.empty_s()){
		if (roott){
			cout << roott->data << " ";
			if (roott->right)
				s.push_s(roott->right);
			roott = roott->left;
		}
		else
			roott = s.pop_s();
	}
}

template<class T>		//中序遍历
void btree<T>::traversal_inorder_bt()const
{/*以t指向的结点是否存在为中心，判断根结点是否为最左子树。
 如果存在，则该根结点不是最左子树，需要入栈；不存在则根为最左子树，需要进行进一步的操作*/
	if (root == NULL)
		return;
	stack<const btnode*> s;	const btnode *roott;	roott = root;
	while (roott || !s.empty_s()){
		if (roott)		//如果根指针不空  则存入根  并指向左子树，
			{s.push_s(roott);	roott = roott->left;}
		else			//若根指针为空  弹出上一结点t0并输出  并指向右子树
			{roott = s.pop_s();	cout << roott->data << " ";	roott = roott->right;}
	}
}

template<class T>		//后序遍历
void btree<T>::traversal_postorder_bt()const
{/*以t指向的结点是否存在为中心，判断根结点是否为最左子树。
 如果存在，则该根结点不是最左子树，需要入栈；不存在则根为最左子树，需要进行进一步的操作*/
	if (root == NULL)
		return;
	int tag;	stack<int> tags;			//记录结点入栈次数
	stack<const btnode*> s;		//存储结点指针	
	const btnode *roott, *temp;	roott = root;		//temp是为了输出数据后不进入第一个if（roott）的死循环(再次进栈)
	while (roott || !s.empty_s()){
		if (roott){
			s.push_s(roott); tags.push_s(1);	//第一次入栈
			roott = roott->left;
		}
		else {
			temp = s.pop_s(); tag = tags.pop_s();
			if (tag == 1) {						//如果是第二次入栈  则指向右子树  		
				s.push_s(temp); tags.push_s(2);
				roott = temp->right;
			}
			else                               //不是第二次 那就输出
				cout << temp->data << " ";
		}
	}
}

template<class T>		//层次遍历
void btree<T>::level_bt()const{
	if (root == NULL)
		return;
	queue<const btnode*> q;	const btnode *roott;	
	roott = root;	q.push_q(roott);
	while (!q.empty_q()){
		roott = q.pop_q();	cout << roott->data << "  ";
		if (roott->left)
			q.push_q(roott->left);
		if (roott->right)
			q.push_q(roott->right);
	}
}


template<class T>		//清表
void btree<T>::clear_bt(){
	queue<btnode*> q;	q.push_q(root);
	while (!q.empty_q()){
		root = q.pop_q();
		if (root->left)		q.push_q(root->left);
		if (root->right)	q.push_q(root->right);
		delete root;
	}
	size = 0;	root = new btnode;
}

template<class T>		//查找某元素并输出其最短路径
void btree<T>::find_path_bt(const T& x) const{
	stack<const btnode*> s, output; stack<int> tags;
	const btnode *t, *temp;	t = root;	int tag;
	while (t || !s.empty_s()){
		if (t)
			{s.push_s(t);	tags.push_s(1);	t = t->left;}
		else {
			temp = s.pop_s();	tag = tags.pop_s();
			if (tag == 1)
				{s.push_s(temp);	tags.push_s(2);	t = temp->right;}
			else 
				if (temp->data == x)	break;		//相等就跳出循环
		}			
	}
	output.push_s(temp);	tags.clear_s();
	if (temp->date != x)
		{cout << "没有找到该元素!!!" << endl;	return;}	
	while (!s.empty_s())	output.push_s(s.pop_s());		//将数据放到输出栈
	cout << "从根结点到" << x << "的路径为：" << output.pop_s()->data;
	for (tag=1;!output.empty_s();tag++) {				//输出路径	
		if (tag % 10 == 0)
			cout << '\n';
		t = output.pop_s();	cout << " --> " << t->data ;
	}
}

template<class T>		//查找
typename btree<T>::btnode *btree<T>::find_bt(const T& x){
	queue<const btnode*> q;	btnode *roott;	q.push_q(root);
	while (!q.empty_q()){
		roott = q.pop_q();
		if (roott->data == x)	break;
		if (roott->left)	q.push_q(roott->left);
		if (roott->right)	q.push_q(roott->right);
	}
	if (roott->data != x)
		{roott = NULL;	cout << "找不到该元素！" << endl;}
	q.clear_q();	return roott;
}

template<class T>		//复制赋值运算符
const btree<T>& btree<T>::operator=(const btree& bt){//用层次遍历的思路
	if (size > 0)
		clear_bt();
	queue<const btnode*> qbt; queue<btnode*> q;
	const btnode *btroot;	int n = bt.size_bt();
	btnode	*child, *roott;	root->data = bt.root->data;		++size;
	qbt.push_q(bt.root);	q.push_q(root);
	while (size != n){
		btroot = qbt.pop_q();	roott = q.pop_q();		
		if (btroot->left){
			child = new btnode;	child->data = btroot->left->data;
			roott->left = child;	++size;
			qbt.push_q(btroot->left);	q.push_q(child);
		}
		if (btroot->right){
			child = new btnode;	child->data = btroot->right->data;
			roott->right = child;	++size;
			qbt.push_q(btroot->right);	q.push_q(child);
		}
	}	return *this;
}
