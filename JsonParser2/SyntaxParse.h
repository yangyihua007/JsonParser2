
#pragma once

/*
 * 判断字符串本身的合法性
 */
class SyntaxParse
{
public:
	SyntaxParse();
	~SyntaxParse();

	bool  parse(char* value);
};