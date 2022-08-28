#include <string.h>
#include <stdlib.h>
#include "ConcreteObject.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

ConcreteObject::ConcreteObject(OBJ_TYPE  type, char* fdName)
	:Object(type, fdName)
{
	objes = (Object**)malloc(sizeof(Object*)*INCRE_NUM);
	capacity = INCRE_NUM;
	nSize = 0;
}
ConcreteObject::~ConcreteObject()
{
	for(int i = 0; i < nSize; i++) {
        delete *(objes+i);
	}
	free(objes);
}

void ConcreteObject::cout()
{
	if(strlen(getFieldName()) > 0) {
		std::cout << "\"" << getFieldName() << "\"" << ":{" << std::endl;
	} else {
		std::cout << "{" << std::endl;
	}
	Object*  pObj = 0;
	for(int i = 0; i < nSize; i++)
	{
        if(i > 0)
		{
			std::cout << "," << std::endl;
		}
        pObj = *(objes+i);
		pObj->cout();

	}
	std::cout << "}" << std::endl;
}
void ConcreteObject::setField(Object* obj)
{
	if(nSize == capacity) {
		
		Object** pObjes = (Object**)malloc(sizeof(Object*)*(nSize+INCRE_NUM));
	    capacity = INCRE_NUM+nSize;
		for(int i = 0; i < nSize; i++) 
		{
            *(pObjes+i) = *(objes+i);
		}
		free(objes);
		objes = pObjes;
		
	}
	*(objes+nSize) = obj;
	nSize++;
}


