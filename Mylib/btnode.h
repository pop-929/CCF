//¶þ²æÊ÷½áµã
#pragma once

template<class T>
struct btnode {
	T data;
	btnode *left, *right;
	btnode(const T& x=T(),btnode *l=NULL,btnode *r=NULL):data(x),left(l),right(r){}
};

template<class T>
btnode<T> *get_btnode(const T& x = T(), btnode<T> *l = NULL, btnode<T> *r = NULL)
{
	btnode<T> *p = new btnode<T>(x, l, r);
	return p;
}