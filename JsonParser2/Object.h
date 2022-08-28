

#pragma once



enum  OBJ_TYPE
{
	BASIC_INT=1,
	BASIC_STR,
	OBJECT_TYPE,
	ARRAY_TYPE,
	OBJ_END
};


class Object
{
public:
	Object(OBJ_TYPE  type, char* fdName);
	virtual ~Object();

	virtual void cout()=0;
	char* getFieldName();
	void  setFieldName(char* name);
	OBJ_TYPE  getObjType();
private:
	OBJ_TYPE    nType;
	char*       fieldName;

};