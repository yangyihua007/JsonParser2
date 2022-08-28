#include <string.h>
#include "ConcreteObject.h"
#include "BasicObject.h"
#include "ArrayObject.h"
#include "stack.h"
#include "JsonException.h"
#include "JsonParser.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

JsonParser::JsonParser()
{
	prepare();
}
JsonParser::~JsonParser()
{
}
Object*  JsonParser::parse(char*  jsonStr)
{
	int length = strlen(jsonStr);

	bool  bFirstQuote = true;
	char  lastChar = 0;

	// :345, ����ð�ź���ֱ�Ӹ����ֵ�����
	int  dataBeginPos = 0;
	int  dataEndPos = 0;
	bool dataMode = false;

	Object*  pObject = 0;
	Object*  pBasicObject = 0;
	Object*  pArrObject = 0;
	Stack<Object*>  pObjStack;
	char*  pCurValue = 0;
	Object* pCur = 0;
	for(int i = 0; i < length; i++)
	{
		if(*(jsonStr+i) == ' ') 
			continue;
	
        if(*(jsonStr+i) == '{') {
			stack.push('{');
			chrPos.push(i);
			if(lastChar == ':') {
				// ˵�����Ǹ������Ա����
				pObject = new ConcreteObject(OBJECT_TYPE,pCurValue);
				free(pCurValue);
				pObjStack.push(pObject);
			}
			if(lastChar == 0  || lastChar == '[' || lastChar == ',') {
				pObject = new ConcreteObject(OBJECT_TYPE,"");
				pObjStack.push(pObject);
			}
		}
		if(*(jsonStr+i) == '[') {
			stack.push('[');
			chrPos.push(i);
			if(lastChar == ':') {
				// ˵���Ǹ��������
				pArrObject = new ArrayObject(ARRAY_TYPE, pCurValue,OBJ_END);
				free(pCurValue);
				pObjStack.push(pArrObject);
			}
		}

		// 3�����ϵġ��޷�����
		if(*(jsonStr+i) == '\"' && bFirstQuote)
		{
			stack.push('\"');
			chrPos.push(i);
			bFirstQuote = false;
			if(lastChar == ':') {
				// ˵���Ǹ���������ֵ�ĳ�Ա����
				pBasicObject = new BasicObject(BASIC_STR,pCurValue);
				free(pCurValue);
			}
		} else if(*(jsonStr+i) == '\"' && !bFirstQuote) {
			if(stack.pop()!= '\"') {
				std::cout << "The quote doesn't appears in pair" << std::endl;
				throw JsonException();
			}
			int  lastStarPos = chrPos.pop();
			int basicLength = i - lastStarPos-1;
			bFirstQuote = true;
			char*  str = (char*)malloc(basicLength+1);
			memset(str,0,basicLength+1);
			strncpy(str,(jsonStr+lastStarPos+1), basicLength);
			pCurValue = str;
			if(pBasicObject != 0) {
				((BasicObject*)pBasicObject)->setField(pCurValue);
				free(pCurValue);
				if(pObjStack.getTop()->getObjType() == OBJECT_TYPE) {
					((ConcreteObject*)pObjStack.getTop())->setField(pBasicObject);
				}
				if(pObjStack.getTop()->getObjType() == ARRAY_TYPE) {
					((ArrayObject*)pObjStack.getTop())->setField(pBasicObject);
				}
				pBasicObject = 0;  // ����Ϊ�պ���Ҫ����Ȼ�ظ�ʹ��һ������
			}
		}

		if(*(jsonStr+i) == '}') {
			if(stack.isEmpty())
			{
				std::cout << "The " << i <<  "} is illegal" << std::endl;
				throw JsonException();
			}


			if(stack.pop() != '{') {
				std::cout << "Error, the" << i << " char } mismatch!" << std::endl; 
				throw JsonException();
			}
			int objLength = i - chrPos.pop();
			pCur = pObjStack.pop();

			if(!pObjStack.isEmpty()) {
			    if(pObjStack.getTop()->getObjType() == OBJECT_TYPE)
			    {
                    ((ConcreteObject*)pObjStack.getTop())->setField(pCur);
			    }
			    if(pObjStack.getTop()->getObjType() == ARRAY_TYPE) {
			    	((ArrayObject*)pObjStack.getTop())->setField(pCur);
			    }
			}
		}
		if(*(jsonStr+i) == ']') {
			if(stack.isEmpty())
			{
				std::cout << "The " << i <<  "] is illegal" << std::endl;
				throw JsonException();
			}

			if(stack.pop() != '[') {
				std::cout << "Error, the" << i << " char ] mismatch!" << std::endl;
				throw JsonException();
			}
			int arrLength = i - chrPos.pop();

			pCur = pObjStack.pop();
			if(!pObjStack.isEmpty()) {
			    if(pObjStack.getTop()->getObjType() == OBJECT_TYPE)
			    {
                    ((ConcreteObject*)pObjStack.getTop())->setField(pCur);
			    }
			    if(pObjStack.getTop()->getObjType() == ARRAY_TYPE) {
			    	((ArrayObject*)pObjStack.getTop())->setField(pCur);
			    }
			}
		}
		if(*(jsonStr+i) == '\"' || *(jsonStr+i) == ',' || *(jsonStr+i) == ':') {
			if(lastChar != 0) {
			    if(grammar.isIllgalPair(lastChar,*(jsonStr+i))) {
			    	std::cout << "Char " << *(jsonStr+i-1) << "followed with char " << *(jsonStr+i) << " is illegal" << std::endl;
					throw JsonException();
			    }
			}
			
		}


		//////////////////////////////////////////////
		// ����keyName":567  ���ֵ�����
		if(lastChar == ':' && !(*(jsonStr+i) == '{' || *(jsonStr+i) == '[' || *(jsonStr+i) == '\"'))
		{
			// ��ԣ�֮��ֱ������ֵ�������ַ���������, ����׸�����λ��
			dataBeginPos = i;
			dataMode = true;
			pBasicObject = new BasicObject(BASIC_INT,pCurValue);
			free(pCurValue);
		}
		if(*(jsonStr+i) == ',' || *(jsonStr+i) == '}' || *(jsonStr+i) == ']')
		{
			// ������һ�����ֵ�λ��
			if(dataMode) {
			    dataEndPos = i-1;
			    int basicLength = dataEndPos - dataBeginPos + 1;
			    
			    char*  str = (char*)malloc(basicLength+1);
		        memset(str,0,basicLength+1);
		        strncpy(str,(jsonStr+dataBeginPos), basicLength);
		        pCurValue = str;
			    
				if(pBasicObject != 0) {
			        ((BasicObject*)pBasicObject)->setField(pCurValue);
					free(pCurValue);
			        if(pObjStack.getTop()->getObjType() == OBJECT_TYPE) {
			        	((ConcreteObject*)pObjStack.getTop())->setField(pBasicObject);
			        }
			        if(pObjStack.getTop()->getObjType() == ARRAY_TYPE) {
			        	((ArrayObject*)pObjStack.getTop())->setField(pBasicObject);
			        }
				}
				dataMode = false;
				pBasicObject = 0; //

			}
		}
        ///////////////////////////////////////////////

		lastChar = *(jsonStr+i); 
	}
	return pCur;
}
void  JsonParser::prepare()
{
	grammar.setIllgalPair('{', ']');
	grammar.setIllgalPair('{', ':');
	grammar.setIllgalPair('{', ',');
	grammar.setIllgalPair('{', '{');
	
	grammar.setIllgalPair('{','[');
	grammar.setIllgalPair('}','{');
	grammar.setIllgalPair('}','[');
	grammar.setIllgalPair('}',':');
	grammar.setIllgalPair('}','\"');
	grammar.setIllgalPair('[', '}');
	grammar.setIllgalPair('[',':');
	grammar.setIllgalPair('[', ',');
	grammar.setIllgalPair(']','[');
	grammar.setIllgalPair(']','{');
	grammar.setIllgalPair(']','\"');
	grammar.setIllgalPair(']',':');
	grammar.setIllgalPair(',', '}');
	grammar.setIllgalPair(',', ']');
	grammar.setIllgalPair(':', '}');
	grammar.setIllgalPair(':', ']');
	grammar.setIllgalPair('\"', '{');
	grammar.setIllgalPair('\"', '[');
}