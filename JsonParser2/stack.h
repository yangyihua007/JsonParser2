

#pragma once


#define  INCRE_STEP   100
template <typename T>
class Stack
{
public:
	Stack();
	~Stack();
	T  pop();
	void  push(T  p);
	T  getTop();
	bool  isEmpty();
private:
	T*  sBegin;
	int nSize;
	T*  pTop;
};
#include "stack.cpp"