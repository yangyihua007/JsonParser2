#include <string.h>
#include <stdlib.h>
#include "ArrayObject.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

ArrayObject::ArrayObject(OBJ_TYPE type, char* fdName, OBJ_TYPE elemType)
	:Object(type, fdName)
{
    objes = (Object**)malloc(sizeof(Object*)*INCRE_ARRAY_NUM);
	capacity = INCRE_ARRAY_NUM;
	size = 0;
	elementType = elemType;
}
ArrayObject::~ArrayObject()
{
	for(int i = 0; i < size; i++)
	{
        delete *(objes+i);
	}
	free(objes);
}

void  ArrayObject::cout()
{
    std::cout << "\"" << getFieldName() << "\"" << ":[" << std::endl;
    Object*  pObj = 0;
    for(int i = 0; i < size; i++)
	{
        if(i > 0)
		{
           std::cout << ",";
		}
        pObj = *(objes+i);
		pObj->cout();
		
	}
	std::cout << "]" << std::endl;
}

void ArrayObject::setField(Object* object)
{
	if(size == capacity) {
		Object** pObjes = (Object**)malloc(sizeof(Object*)*(size+INCRE_ARRAY_NUM));
	    capacity = INCRE_ARRAY_NUM+size;
		for(int i = 0; i < size; i++) 
		{
            *(pObjes+i) = *(objes+i);
		}
		free(objes);
		objes = pObjes;
		
	}
	*(objes+size) = object;
	size++;
}

void ArrayObject::setElemType(OBJ_TYPE  type)
{
	elementType = type;
}