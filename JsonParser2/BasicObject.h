
#pragma once
#include "Object.h"

class BasicObject: public Object
{
public:
	BasicObject(OBJ_TYPE type,char* fieldName);
	virtual ~BasicObject();

	virtual void cout();

	void setField(char*  p);
private:
	char*  pValue;
	
};