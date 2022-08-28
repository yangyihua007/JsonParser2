

#pragma once

#include "Object.h"

#define  INCRE_NUM  100
class ConcreteObject: public Object
{
public:
	ConcreteObject(OBJ_TYPE  type, char* fdName);
	virtual ~ConcreteObject();

	virtual void cout();
	void  setField(Object* obj);
private:

	Object**  objes;
	int       nSize;
	int       capacity;
};
