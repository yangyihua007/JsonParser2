
#pragma once
#include "grammar.h"
#include "stack.h"
#include "Object.h"
#include "SyntaxParse.h"


class JsonParser
{
public:
	JsonParser();
	~JsonParser();

	/*
	 * ��ʼ���Ƿ����﷨
	 */
	void  prepare();
	Object*  parse(char*  jsonStr);
private:
	Grammar  grammar;  
	Stack<char>    stack;
    Stack<int>     chrPos; // ��¼����ַ���λ��
	SyntaxParse    syntaxParse;
};