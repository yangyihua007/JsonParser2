#ifndef STACK_H
#define STACK_H
#include <string.h>
#include "stack.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

template <typename T>
Stack<T>::Stack()
{
    sBegin = new T[INCRE_STEP];
	nSize = INCRE_STEP;
	pTop = sBegin;
}
template <typename T>
Stack<T>::~Stack()
{
	delete [] sBegin;
}
template <typename T>
T  Stack<T>::pop()
{
	if(pTop == sBegin) {
		cout << "Empty stack" << std::endl;
		return 0;
	}
	T a =  *(pTop-1);
	*(pTop - 1)=0;
	pTop = pTop - 1;
	return a;
}
template <typename T>
void  Stack<T>::push(T  p)
{
	int curSize = (pTop - sBegin)/sizeof(T);
	if(curSize >= nSize) {
		T*  p = new T[nSize + INCRE_STEP];
		memcpy(p, sBegin, nSize*sizeof(T));
		pTop = p+nSize;
		delete [] sBegin;
		sBegin = p;
		nSize = nSize + INCRE_STEP;
		
	}
	*pTop = p;
	pTop = pTop+1;
}
template <typename T>
T  Stack<T>::getTop()
{
	return *(pTop-1);
}

template <typename T>
bool  Stack<T>::isEmpty()
{
	return pTop == sBegin;
}
#endif