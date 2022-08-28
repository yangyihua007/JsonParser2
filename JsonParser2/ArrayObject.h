
#pragma once
#include "Object.h"

#define  INCRE_ARRAY_NUM 20
class ArrayObject: public Object
{
public:
	ArrayObject(OBJ_TYPE type, char* fdName, OBJ_TYPE elemType);
	virtual ~ArrayObject();

	void setField(Object* object);
	virtual void  cout();
	void  setElemType(OBJ_TYPE  type);
private:
	Object**  objes;
	OBJ_TYPE  elementType;
	int       size;
	int       capacity;
};