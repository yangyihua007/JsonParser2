#include <string.h>
#include "BasicObject.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

BasicObject::BasicObject(OBJ_TYPE type,char* fieldName)
	:Object(type, fieldName)
{
	pValue = 0;
}
BasicObject::~BasicObject()
{
	free(pValue);
}
void BasicObject::cout()
{
    if(getObjType() == BASIC_INT) {
	    std::cout <<  "\"" << getFieldName() << "\""  << ":" << pValue;
	}
    if(getObjType() == BASIC_STR) {
		char*  p = getFieldName();
		std::cout <<  "\"" << getFieldName() << "\""  << ":" << "\"" << pValue << "\"";
	}
}

void BasicObject::setField(char*  p)
{
    int  length = strlen(p)+1;
	pValue = (char*)malloc(length);
	memset(pValue,0, length);
	strncpy(pValue, p, strlen(p));
}
