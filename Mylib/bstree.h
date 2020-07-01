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
	void insert(const T&, btnode*&);				//����Ԫ��
	void remove(const T&, btnode*&);				//ɾ��Ԫ��
	btnode *find_min(btnode*)const;					//������СԪ�صĽ��ָ��
	btnode *find_max(btnode*)const;					//�������Ԫ�صĽ��ָ��
	btnode *find_node(const T&, btnode*)const;		//����ĳһԪ�صĽ��ָ��
	void clear(btnode*&);							//���
	void printbtree(const btnode*, int)const;		//��ֱ���
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
	T& find_min_bs()const { return find_min(root)->data; }			//������СԪ��
	T& find_max_bs()const { return find_max(root)->data; }			//�������Ԫ��
	bool find_bs(const T& x)const { return find_node(x, root) != NULL; }	//����
	void printbtree_bs(int w)const { printbtree(root, w); }					//��ֱ���
	void traversal_inorder_bs()const;					//�������
	bool find_bs(T&)const;								//���Ҳ���ȡ
	bool empty_bs()const { return size == 0; }			//�п�
	int size_bs() { return size; }						//ȡԪ�ظ���


	void clear_bs() { clear(root); }					//���
	void updata_bs(const T&);							//�޸�
	void insert_bs(const T& x) { insert(x, root); }		//����
	void remove_bs(const T& x) { remove(x, root); }		//ɾ��	
};

template<class T>		//����Ԫ��
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

template<class T>		//ɾ��Ԫ��
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

template<class T>		//������СԪ�صĽ��ָ��
typename bstree<T>::btnode * bstree<T>::find_min(btnode *t) const{
	if (t != NULL)
		while (t->left != NULL)
			t = t->left;
	return t;
}

template<class T>		//�������Ԫ�صĽ��ָ��
typename bstree<T>::btnode * bstree<T>::find_max(btnode *t) const{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

template<class T>		//����ĳһԪ�صĽ��ָ��
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

template<class T>		//���
void bstree<T>::clear(btnode* &t){
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;	t = NULL;
}

struct location { int xindent, ylevel; };		//�������λ��
void gotoxy(int x, int y) {			//���λ��
	static int level = 0, indent = 0;
	if (y == 0)						//�������������ʱҪ���¸�ֵ
	{
		indent = 0; level = 0;
	}
	if (level != y)					//���������ӣ�����������0��ʼ
	{
		cout << endl;	indent = 0; level++;
	}
	cout.width(x - indent);			//��������������ȷ����ǰ������
	indent = x;						//��¼��ǰ������
}
template<class T>		//��ֱ���
void bstree<T>::printbtree(const btnode *t,int screenwidth)const {
	if (t == NULL)
		return;
	const btnode *roott = t;
	int level = 0, offset = screenwidth / 2;			//��0�㿪ʼ������������Ļ��ȵ�һ��
	location floc, cloc;								//��¼˫�׺ͺ��ӽ������λ�õı���
	queue<const btnode*> q;								//������ָ��Ķ���
	queue<location> lq;									//���������λ�õĶ���
	floc.xindent = offset;	floc.ylevel = level;		//��������λ��
	q.push_q(roott);	lq.push_q(floc);				//��ָ�����//�����λ���������				
	while (!q.empty_q()) {
		roott = q.pop_q();	floc = lq.pop_q();
		gotoxy(floc.xindent, floc.ylevel);				//ȷ��������λ��
		cout << roott->data;							//������
		if (floc.ylevel != level)						//������1������������
		{
			level++; offset = offset / 2;
		}
		if (roott->left) {			//���������		
			q.push_q(roott->left);	cloc.ylevel = floc.ylevel + 1;				//�����������λ��
			cloc.xindent = floc.xindent - offset / 2;	lq.push_q(cloc);		//�������λ�����
		}
		if (roott->right) {
			q.push_q(roott->right);	cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent + offset / 2;	lq.push_q(cloc);
		}
	}	cout << endl;
}

template<class T>		//�������
void bstree<T>::traversal_inorder_bs() const{
	btnode *t = root;	stack<btnode*> s;	s.push_s(t);
	while (t||!s.empty_s()) {
		if(t)
			{s.push_s(t);	t = t->left;}
		else 
			{t = s.pop_s();	cout << t->data << ' ';	t = t->right;}
	}
}

template<class T>		//���Ҳ���ȡ
inline bool bstree<T>::find_bs(T& x)const {
	btnode *p = find_node(x, root);
	if (p)
		{x = p->data;	return 1;}
	return 0;
}

template<class T>		//�޸�
void bstree<T>::updata_bs(const T& x){
	btnode *p = find_node(x, root);
	if (p)
		p->data = x;
	else
		insert(x);
}