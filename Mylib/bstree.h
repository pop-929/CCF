#pragma once
#include"stack_and_queue.h"


template<class T>
class bstree {
	struct btnode {
		T data;
		btnode *left, *right;
		btnode(const T& x, btnode *l = NULL, btnode *r = NULL) :data(x), left(l), right(r) {};
	};
	btnode *root;
	int size;
	void insert(const T&, btnode*&);				//插入元素
	void remove(const T&, btnode*&);				//删除元素
	btnode *find_min(btnode*)const;					//返回最小元素的结点指针
	btnode *find_max(btnode*)const;					//返回最大元素的结点指针
	btnode *find_node(const T&, btnode*)const;		//返回某一元素的结点指针
	void clear(btnode*&);							//清表
	void printbtree(const btnode*, int)const;		//垂直输出
public:
	class const_iterator {
	protected:
		btnode *current;
		T& retrieve()const { return current->data; }
		const_iterator(btnode *t) { current = go_far_left(t); }
		stack<btnode*> st;
		btnode *go_far_left(btnode *t) {
			if (!t)
				return NULL;
			while(t->left)
				{st.push_s(t);	t = t->left;}
			return t;
		}
		friend class bstree<T>;
	public:
		const_iterator() :current(NULL) {};
		const T& operator*()const { return retrieve(); }
		const_iterator& operator++() {
			if (current->right)
				current = go_far_left(current->right);
			else 
				if (!st.empty_s())
					current = st.pop_s();
				else
					current = NULL;
			return *this;
		}
		bool operator==(const const_iterator& rhs)const { return current == rhs.current; }
		bool operator!=(const const_iterator& rhs)const { return current != rhs.current; }
	};
	class iterator :public const_iterator {
	protected:
		iterator(btnode *t) :const_iterator(t) {};
		friend class bstree<T>;
		using const_iterator::retrieve;
		using const_iterator::current;
		using const_iterator::st;
		using const_iterator::go_far_left;
	public:
		iterator() {};
		T& operator*() { return retrieve(); }
		const T&operator*()const { return const_iterator::operator*(); }
		iterator& operator++() {
			if (current->right)
				current = go_far_left(current->right);
			else
				if (!st.empty_s())
					current = st.pop_s();
				else
					current = NULL;
			return *this;
		}
	};
	const_iterator begin()const { return const_iterator(root); }
	const_iterator end()const { return NULL; }
	iterator begin(){ return iterator(root); }
	iterator end(){ return NULL; }

	bstree() :root(NULL), size(0) {};
	~bstree() { clear_bs(); }
	T& find_min_bs()const { return find_min(root)->data; }			//返回最小元素
	T& find_max_bs()const { return find_max(root)->data; }			//返回最大元素
	bool find_bs(const T& x)const { return find_node(x, root) != NULL; }	//查找
	void printbtree_bs(int w)const { printbtree(root, w); }					//垂直输出
	void traversal_inorder_bs()const;					//中序遍历
	bool find_bs(T&)const;								//查找并提取
	bool empty_bs()const { return size == 0; }			//判空
	int size_bs() { return size; }						//取元素个数


	void clear_bs() { clear(root); }					//清表
	void updata_bs(const T&);							//修改
	void insert_bs(const T& x) { insert(x, root); }		//插入
	void remove_bs(const T& x) { remove(x, root); }		//删除	
};

template<class T>		//插入元素
inline void bstree<T>::insert(const T& x, btnode* &t){
	if (t == NULL)
		{t = new btnode(x);	++size;}
	else
		if (x < t->data)
			insert(x, t->left);
		else
			if (t->data < x)
				insert(x, t->right);
}

template<class T>		//删除元素
inline void bstree<T>::remove(const T& x, btnode* &t){
	if (t == NULL)
		return;
	if (x < t->data)
		remove(x, t->left);
	else
		if (t->data < x)
			remove(x, t->right);
		else
			if (t->left != NULL && t->right != NULL) {
				t->data = find_min(t->right)->data;
				remove(t->data, t->right);
			}else {
				btnode *old = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete old;	--size;
			}
}

template<class T>		//返回最小元素的结点指针
typename bstree<T>::btnode * bstree<T>::find_min(btnode *t) const{
	if (t != NULL)
		while (t->left != NULL)
			t = t->left;
	return t;
}

template<class T>		//返回最大元素的结点指针
typename bstree<T>::btnode * bstree<T>::find_max(btnode *t) const{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

template<class T>		//返回某一元素的结点指针
typename bstree<T>::btnode * bstree<T>::find_node(const T& x, btnode *t) const{
	if (t == NULL)
		return NULL;
	while (t) 
		if (x < t->data)
			t = t->left;
		else if (t->data < x)
				t = t->right;
			 else return t;
	return NULL;
}

template<class T>		//清表
void bstree<T>::clear(btnode* &t){
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;	t = NULL;
}

struct location { int xindent, ylevel; };		//结点坐标位置
void gotoxy(int x, int y) {			//输出位置
	static int level = 0, indent = 0;
	if (y == 0)						//重新输出二叉树时要重新赋值
	{
		indent = 0; level = 0;
	}
	if (level != y)					//若层数增加，则缩进量从0开始
	{
		cout << endl;	indent = 0; level++;
	}
	cout.width(x - indent);			//根据已有缩进量确定当前缩进量
	indent = x;						//记录当前缩进量
}
template<class T>		//垂直输出
void bstree<T>::printbtree(const btnode *t,int screenwidth)const {
	if (t == NULL)
		return;
	const btnode *roott = t;
	int level = 0, offset = screenwidth / 2;			//从0层开始，缩进量是屏幕宽度的一半
	location floc, cloc;								//记录双亲和孩子结点的输出位置的变量
	queue<const btnode*> q;								//储存结点指针的队列
	queue<location> lq;									//储存结点输出位置的队列
	floc.xindent = offset;	floc.ylevel = level;		//根结点输出位置
	q.push_q(roott);	lq.push_q(floc);				//根指针入队//根结点位置数据入队				
	while (!q.empty_q()) {
		roott = q.pop_q();	floc = lq.pop_q();
		gotoxy(floc.xindent, floc.ylevel);				//确定输出光标位置
		cout << roott->data;							//输出结点
		if (floc.ylevel != level)						//层数加1，缩进量减半
		{
			level++; offset = offset / 2;
		}
		if (roott->left) {			//如果有左孩子		
			q.push_q(roott->left);	cloc.ylevel = floc.ylevel + 1;				//计算左孩子输出位置
			cloc.xindent = floc.xindent - offset / 2;	lq.push_q(cloc);		//左孩子输出位置入队
		}
		if (roott->right) {
			q.push_q(roott->right);	cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent + offset / 2;	lq.push_q(cloc);
		}
	}	cout << endl;
}

template<class T>		//中序遍历
void bstree<T>::traversal_inorder_bs() const{
	btnode *t = root;	stack<btnode*> s;	s.push_s(t);
	while (t||!s.empty_s()) {
		if(t)
			{s.push_s(t);	t = t->left;}
		else 
			{t = s.pop_s();	cout << t->data << ' ';	t = t->right;}
	}
}

template<class T>		//查找并提取
inline bool bstree<T>::find_bs(T& x)const {
	btnode *p = find_node(x, root);
	if (p)
		{x = p->data;	return 1;}
	return 0;
}

template<class T>		//修改
void bstree<T>::updata_bs(const T& x){
	btnode *p = find_node(x, root);
	if (p)
		p->data = x;
	else
		insert(x);
}