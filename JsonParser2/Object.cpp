#include <iostream>
using namespace std;
#include "Object.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

Object::Object(OBJ_TYPE  type, char* fdName)
{
	nType = type;
	fieldName = (char*)malloc(strlen(fdName)+1);
	memset(fieldName,0, (strlen(fdName)+1));
	strncpy(fieldName,fdName, strlen(fdName));
}
Object::~Object()
{
	free(fieldName);
}
void Object::cout()
{
}

char*  Object::getFieldName()
{
	return fieldName;
}

void   Object::setFieldName(char* name)
{
	fieldName = name;
}

OBJ_TYPE  Object::getObjType()
{
	return nType;
}
