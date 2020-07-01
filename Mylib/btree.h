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
	btnode *root;			//�����������
	int size;				//������
	void init_bt() { size = 0;	root = new btnode; }
public:
	btree() :root(NULL) { init_bt(); };						//Ĭ�Ϲ��캯�������ɿ�������������
	btree(const btree<T>& bt) { init_bt(); operator=(bt); }	//���ƹ��캯��
	~btree() { clear_bt(); delete root; }					//������

	bool empty_bt()const{ return size == 0; }	//�п�
	int size_bt()const  { return size; }		//ȡ�����
	int depth_bt()const;						//������
	void print_bt(int)const;					//��ֱ���������
	void traversal_preorder_bt()const;			//ǰ�����
	void traversal_inorder_bt()const;			//�������
	void traversal_postorder_bt()const;			//�������
	void level_bt()const;						//��α���

	void make_bt();						//�����Զ��������
	void make_complete_bt();			//���ٴ�����ȫ������
	void make_pre_and_ino_bt(const T*, const T*,int);		//��ǰ����������д���������
	void make_post_and_ino_bt(const T*, const T*,int);		//�ɺ�����������д���������	
	void make_complete_bt(const char*);			//���ļ��ж�ȡ��������ȫ���������Բв��ã�
	btnode *vec_to_link_bt(const vector<T>&);	//��������˳��洢�ṹת��Ϊ��ʽ�洢
	const btree& operator=(const btree&);		//���Ƹ�ֵ�����
	void write_bt(const char*);					//��������д���ļ�
	
	btnode begin_bt() { return root->left; }			//ȡ������ָ��
	btnode begin_bt()const	{ return root->left; }		//ȡconst��������ָ��
	const T& front_bt()const{ return *begin_bt(); }		//����const����Ԫ������	
	T& front_bt() { return *begin_bt(); }				//������Ԫ������
	void clear_bt();						//���
	btnode *find_bt(const T&);				//����ĳԪ�ز�����ָ��
	void find_path_bt(const T&)const;		//����ĳԪ�ز���������·��
};


template<class T>		//������
int btree<T>::depth_bt()const{
	if (!root)			//�������Ϊ0
		return 0;
	int depth = 0, i;			//��Ⱥ�ÿ��Ľ�����
	queue<btnode*> q;	btnode *temp;	temp = root;	q.push_q(temp);
	while (!q.empty_q()){
		i = q.size_q();			//ÿ��Ľ��������ڶ��������ݵĸ���
		depth++;	
		while (i--)	{
			temp = q.pop_q();	//�������
			if (temp->left)		q.push_q(temp->left);		//���������
			if (temp->right)	q.push_q(temp->right);		//���������
		}
	}	return depth;
}

template<class T>		//�����Զ��������
void btree<T>::make_bt(){
	int floor = 1, lorr = 0, sum = 1, sum_now = 0, num = 0;	// lorr:�������Һ��ӣ�lorr%2==0���Һ��ӣ����������ӣ�.
				// floor:���ĵ�ǰ���. sum:��һ��ǿս��ĸ���. num:��һ����ı��. sum_now����ǰ��ķǿս�����.
	btnode *p=new btnode, *child;		//��ǰ���ʹ��������
	cout << '\n' << "����ʹ��make_bt�����Զ����������" << '\n' 
	 	 << "1��Y�������ݽ�㣻0��N���ÿսڵ㣻5��C�鿴��������9�������롣 " 
		 << '\n' << "�� 0 ��:" << '\n' << "�������������ݣ�";
	cin >> root->data;	size++;		cout << '\n' << "�� 1 ��:" << endl;
	queue<btnode*> q;	q.push_q(root);				//��������
	while (!q.empty_q() || lorr % 2 == 1){
		++lorr;
		if (lorr % 2 == 1)
			{++num;	p = q.pop_q();}		//����ӣ���ż�һ����һ���ְ� //�ְֳ�ɽ
		if (num > sum){					//�����Ŵ��ڽڵ��������ܵ���һ��
			sum = sum_now; floor++; num = 1; sum_now = 0;		//��ʼ����������
			cout << '\n' << "�� " << floor << " �㣺" << endl;
		}
		if (lorr % 2 == 1)	cout << "��ǰΪ����ӣ�";
		else  cout << "��ǰΪ�Ҷ��ӣ�";
		char leaf_flag;					//�Ƿ������
	here0:
		cout << "�ְ���( " << p->data << " )  �����ǿս�㣿��1/0/9����";
	here1:
		cin >> leaf_flag;
		switch (leaf_flag){
			//�ս�㣨ʲô����������������������NULL��
		case '0':	case 'n':	case 'N':	 break;
			//�ǿս��
		case '1':	case 'y':	case 'Y':
			child = new btnode;			//������������㣩		
			cout << "���������ݣ�";
			cin >> child->data;							//��������			
			if (lorr % 2 == 1)							//����Ϊ1˵��������
				p->left = child;						//���ڵ���ָ��ָ�������						
			else
				p->right = child;						//���ڵ���ָ��ָ�������	
			q.push_q(child);							//�����ӳɳ�
			++sum_now;	size++; 	break;				//��ǰ�������ݽڵ������1			
			//�鿴��ǰ������
		case '5':	case 'c':	case 'C':	cout << "��ǰ��������" << size << endl;	goto here0;		break;
			//��������
		case '9':	q.~queue();	return;
			//���������
		default:	cout << "���������������룺"; goto here1;	break;
		}
	}
}

template<class T>		//���ٴ�����ȫ������
void btree<T>::make_complete_bt(){
	int lorr = 0;				// �������Һ��ӣ�lorr%2==1�����ӣ��������Һ��ӣ�.
	queue<btnode*> q;	T temp;	btnode *p, *child;	p = root;	
	cout << "����ʹ�ÿ��ٽ�����ȫ��������" << '\n' << "����������������ղ�ε�˳�����룬EOF������" << endl;
	cin >> temp;	root->data = temp;	q.push_q(root);
	while (cin >> temp){		//ֱ������EOF�Ž���(ctrl+z�ͻس�)
		++lorr;	child = new btnode;	child->data = temp;
		if (lorr % 2 == 1)
			{p = q.pop_q();	p->left = child;}		//�ְֳ�ɽ,�������
		else
			p->right = child;	//���Ҷ���
		++size;	q.push_q(child);
	}	cin.clear();	//��������״̬��ʹ֮��Ч
}

template<class T>		//��������˳��洢�ṹת��Ϊ��ʽ�洢
typename btree<T>::btnode * btree<T>::vec_to_link_bt(const vector<T>& l)
{//���ʱ���Ǹ����ӣ�������ʱ��ͱ���˰ְ�
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

template<class T>		//���ļ��ж�ȡ��������ȫ������(�������)
void btree<T>::make_complete_bt(const char* filename){
	ifstream fin(filename, ios::in);			//���ļ�		֮��Ϳ��ٴ�����ȫ������һ��
	if (!fin)
		{cout << "���ļ� " << filename << " ʧ�ܣ�" << endl;	return;}
	int lorr = 0;	queue<btnode*> q;			// �������Һ��ӣ�lorr%2==1�����ӣ��������Һ��ӣ�.

	btnode *p, *child = new btnode;	p = root;
	fin >> root->data;	q.push_q(root);		++size;
	while (!fin.eof()) {			//���ļ��׽���	
		++lorr;		child = new btnode;
		fin >> child->data;
		if (lorr % 2 == 1)
			{p = q.pop_q();	p->left = child;}	//�ְֳ�ɽ,�������			
		else
			p->right = child;	//���Ҷ���
		size++;		q.push_q(child);
	}
	if (p->left == child)
		p->left = NULL;
	if (p->right == child)
		p->right = NULL;
	delete child;	--size;	fin.close();
}

template<class T>		//��������д���ļ�
void btree<T>::write_bt(const char* filename){
	ofstream fout(filename, ios::out);				//���ļ�		֮��Ϳ��ٴ�����ȫ������һ��
	if (!fout)
		{cout << "���ļ� " << filename << " ʧ�ܣ�" << endl;	return;}
	if (!root)					//����
		return;
	int depth = 0, i, n = 1;			//��Ⱥ�ÿ��Ľ�����
	queue<btnode*> q;	btnode *temp;	temp = root;	q.push_q(temp);
	fout << "-----�� 0 ��-----��" << '\n' << root->data << "  ";
	while (n != size){
		i = q.size_q();		depth++;	//ÿ��Ľ��������ڶ��������ݵĸ���
		
		fout << '\n' << "-----�� " << depth << " ��-----��" << '\n';
		while (i--){		
			temp = q.pop_q();	//�������
			if (temp->left) { 	//���������			 
				q.push_q(temp->left);	++n;
				fout << "��������" << temp->left->data << " -->���ڵ㣺" << temp->data << endl;
			}
			if (temp->right) {	//���������			
				q.push_q(temp->right);	++n;
				fout << "��������" << temp->right->data << " -->���ڵ㣺" << temp->data << endl;
			}
		}
	}	fout.close();	
}

template<class T>		//��ǰ����������д���������
void btree<T>::make_pre_and_ino_bt(const T *pre, const T *ino, int n)
{/* btΪ����������������������bt�ڸ��ڵ���ߣ�i_site<fi_site��
		1�����������ȣ����ڵ������±�-bt�����±�-1��	fi_site-i_site-1��
		2�����������ȣ����ܳ�-����������-1��			leng-r_num-1��
	btΪ����������������������bt�ڸ��ڵ��ұߣ�i_site>fi_site��
		1�����������ȣ�bt�����±�-���ڵ������±�-1��	i_site-fi_site-1��
		2�����������ȣ����ܳ�-����������-1��			leng-l_num-1��
	�����±꣺btǰ���±�+1��				p_site+1��
	�Һ����±꣺btǰ���±�+����������+1��	p_site+l_num+1��*/
	stack<btnode*> s;	stack<int> p, i, l, fi;	//����ջ,ǰ�������±�ջ������ջ������������±�ջ
	int p_site, i_site = 0, fi_site = n;			//ǰ�������±ꡣ����������±�
	int leng = n, old_leng = 0, l_num, r_num, x;	//��������һ������������������
	btnode *bt, *child;	root->data = pre[0];	++size;	//��ǰ��㡣���ӽ��	
	for (x = 0; x < n; x++)
		if (root->data == ino[x])	break;
	s.push_s(root);		l.push_s(n);	p.push_s(0);	i.push_s(x);
	while (size != n){
		bt = s.pop_s();		leng = l.pop_s();		//��ǰ��㡢��������
		p_site = p.pop_s();	i_site = i.pop_s();		//��ǰ���ǰ�������±����
		if (leng == 1) {			//�����Ҷ�ӽ�㣬ֱ�ӽ�����һ��ѭ��		
			fi_site = fi.pop_s();	//��Ѱ����һ���������������ĸ����������±�
			old_leng = 1;	continue;			//Ҷ�ӽ��ı�־		
		}
		if (i_site < fi_site)		//��bt�����������������������ڸ��ڵ���ߣ����������������ȵĹ�ϵ(��ʼ�ĸ����Ĭ��Ϊ������)
			{r_num = fi_site - i_site - 1;	l_num = leng - r_num - 1;}
		else 						//bt�����������������ȼ��㷽����btΪ��������һ��
			{l_num = i_site - fi_site - 1;	r_num = leng - l_num - 1;}
		child = new btnode;			++size;		//�½����ӽ��
		if (l_num > 0 && old_leng != 1) {				//�������bt������������һ������Ҷ��		
			if (r_num > 0) {			//���������������Ҫ����ǰ������Ϣ��������			
				s.push_s(bt);	l.push_s(leng);		fi.push_s(fi_site);
				p.push_s(p_site);	i.push_s(i_site);
			}
			child->data = pre[p_site + 1];
			bt->left = child;	l.push_s(l_num);		//�϶��ӡ�����������ѹ��ջ��
			for (x = i_site - l_num; x < i_site; x++)	//��ǰ���-����������Ϊ��ʼ�㣬��������ǰ���
				if (child->data == ino[x])	break;
			s.push_s(child);	p.push_s(p_site + 1);	i.push_s(x);	//���ӣ�����ǰ�������±�ѹ��ջ
		}
		else {
			child->data = pre[p_site + l_num + 1];
			bt->right = child;	l.push_s(r_num);
			for (x = i_site + 1; x < fi_site; x++)		//��ǰ���+1Ϊ��ʼ�㣬������������ڵ��λ��
				if (child->data == ino[x])	break;
			s.push_s(child);	p.push_s(p_site + l_num + 1);	i.push_s(x);	//������ѹջ			
		}	fi_site = i_site;	old_leng = leng;	
	}
}

template<class T>		//�ɺ�����������д���������
void btree<T>::make_post_and_ino_bt(const T *post, const T *ino, int n)
{/*	�����±꣺bt�����±�-����������-1��p_site-r_num-1��
	�Һ����±꣺bt�����±�-1��p_site-1�� */
	stack<btnode*> s;	stack<int> p, i, l, fi;	//�������±�ջ������ջ������������±�ջ
	int p_site, i_site = 0, fi_site = n;			//�������±ꡣ����������±�
	int leng = n, old_leng = 0, l_num, r_num, x;	//��������һ������������������
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
			child->data = post[p_site - r_num - 1];			//�����±꣺bt�����±�-����������-1��p_site-r_num-1��			
			bt->left = child;	s.push_s(child);
			for (x = i_site - l_num; x < i_site; x++)		//������λ�õ�ǰ��������λ�ÿ�ʼ��������������ڵ�λ��
				if (child->data == ino[x])	break;
			l.push_s(l_num);	p.push_s(p_site - r_num - 1);	i.push_s(x);
		}
		else {
			child->data = post[p_site - 1];					//�Һ����±꣺bt�����±� - 1��p_site - 1��
			bt->right = child;	s.push_s(child);
			for (x = i_site + 1; x < fi_site; x++)			//�ӵ�ǰλ��+1��ʼ��������������ڵ��λ��
				if (child->data == ino[x])	break;
			l.push_s(r_num);	p.push_s(p_site - 1);	i.push_s(x);
		}	fi_site = i_site;	old_leng = leng;		
	}
}


struct location { int xindent, ylevel; };		//�������λ��
void gotoxy(int x, int y) {			//���λ��
	static int level = 0, indent = 0;
	if (y == 0)						//�������������ʱҪ���¸�ֵ
		{indent = 0; level = 0;}
	if (level != y)					//���������ӣ�����������0��ʼ
		{cout << endl;	indent = 0; level++;}
	cout.width(x - indent);			//��������������ȷ����ǰ������
	indent = x;						//��¼��ǰ������
}
template<class T>		//��ֱ���������
void btree<T>::print_bt(int screenwidth)const{
	if (root == NULL)
		return;
	const btnode *roott; roott = root;
	int level = 0, offset = screenwidth / 2;			//��0�㿪ʼ������������Ļ��ȵ�һ��
	location floc, cloc;								//��¼˫�׺ͺ��ӽ������λ�õı���
	queue<const btnode*> q;								//������ָ��Ķ���
	queue<location> lq;									//���������λ�õĶ���
	floc.xindent = offset;	floc.ylevel = level;		//��������λ��
	q.push_q(roott);	lq.push_q(floc);				//��ָ�����//�����λ���������				
	while (!q.empty_q()){
		roott = q.pop_q();	floc = lq.pop_q();
		gotoxy(floc.xindent, floc.ylevel);				//ȷ��������λ��
		cout << roott->data;							//������
		if (floc.ylevel != level)						//������1������������
			{level++; offset = offset / 2;}
		if (roott->left) {			//���������		
			q.push_q(roott->left);	cloc.ylevel = floc.ylevel + 1;				//�����������λ��
			cloc.xindent = floc.xindent - offset / 2;	lq.push_q(cloc);		//�������λ�����
		}
		if (roott->right){
			q.push_q(roott->right);	cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent + offset / 2;	lq.push_q(cloc);
		}
	}	cout << endl;	
}


template<class T>		//ǰ�����
void btree<T>::traversal_preorder_bt()const
{/*��tָ��Ľ���Ƿ����Ϊ���ģ��жϸ�����Ƿ�Ϊ����������
 ������ڣ������㲻��������������Ҫ���������������������Ϊ������������Ҫ���н�һ���Ĳ���*/
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

template<class T>		//�������
void btree<T>::traversal_inorder_bt()const
{/*��tָ��Ľ���Ƿ����Ϊ���ģ��жϸ�����Ƿ�Ϊ����������
 ������ڣ���ø���㲻��������������Ҫ��ջ�����������Ϊ������������Ҫ���н�һ���Ĳ���*/
	if (root == NULL)
		return;
	stack<const btnode*> s;	const btnode *roott;	roott = root;
	while (roott || !s.empty_s()){
		if (roott)		//�����ָ�벻��  ������  ��ָ����������
			{s.push_s(roott);	roott = roott->left;}
		else			//����ָ��Ϊ��  ������һ���t0�����  ��ָ��������
			{roott = s.pop_s();	cout << roott->data << " ";	roott = roott->right;}
	}
}

template<class T>		//�������
void btree<T>::traversal_postorder_bt()const
{/*��tָ��Ľ���Ƿ����Ϊ���ģ��жϸ�����Ƿ�Ϊ����������
 ������ڣ���ø���㲻��������������Ҫ��ջ�����������Ϊ������������Ҫ���н�һ���Ĳ���*/
	if (root == NULL)
		return;
	int tag;	stack<int> tags;			//��¼�����ջ����
	stack<const btnode*> s;		//�洢���ָ��	
	const btnode *roott, *temp;	roott = root;		//temp��Ϊ��������ݺ󲻽����һ��if��roott������ѭ��(�ٴν�ջ)
	while (roott || !s.empty_s()){
		if (roott){
			s.push_s(roott); tags.push_s(1);	//��һ����ջ
			roott = roott->left;
		}
		else {
			temp = s.pop_s(); tag = tags.pop_s();
			if (tag == 1) {						//����ǵڶ�����ջ  ��ָ��������  		
				s.push_s(temp); tags.push_s(2);
				roott = temp->right;
			}
			else                               //���ǵڶ��� �Ǿ����
				cout << temp->data << " ";
		}
	}
}

template<class T>		//��α���
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


template<class T>		//���
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

template<class T>		//����ĳԪ�ز���������·��
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
				if (temp->data == x)	break;		//��Ⱦ�����ѭ��
		}			
	}
	output.push_s(temp);	tags.clear_s();
	if (temp->date != x)
		{cout << "û���ҵ���Ԫ��!!!" << endl;	return;}	
	while (!s.empty_s())	output.push_s(s.pop_s());		//�����ݷŵ����ջ
	cout << "�Ӹ���㵽" << x << "��·��Ϊ��" << output.pop_s()->data;
	for (tag=1;!output.empty_s();tag++) {				//���·��	
		if (tag % 10 == 0)
			cout << '\n';
		t = output.pop_s();	cout << " --> " << t->data ;
	}
}

template<class T>		//����
typename btree<T>::btnode *btree<T>::find_bt(const T& x){
	queue<const btnode*> q;	btnode *roott;	q.push_q(root);
	while (!q.empty_q()){
		roott = q.pop_q();
		if (roott->data == x)	break;
		if (roott->left)	q.push_q(roott->left);
		if (roott->right)	q.push_q(roott->right);
	}
	if (roott->data != x)
		{roott = NULL;	cout << "�Ҳ�����Ԫ�أ�" << endl;}
	q.clear_q();	return roott;
}

template<class T>		//���Ƹ�ֵ�����
const btree<T>& btree<T>::operator=(const btree& bt){//�ò�α�����˼·
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
