
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
	 * 初始化非法的语法
	 */
	void  prepare();
	Object*  parse(char*  jsonStr);
private:
	Grammar  grammar;  
	Stack<char>    stack;
    Stack<int>     chrPos; // 记录配对字符的位置
	SyntaxParse    syntaxParse;
};