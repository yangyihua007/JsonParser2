
#pragma once



#define  MAX_ILLGALPAIR   32
class Grammar
{
public:
	Grammar();
	~Grammar();

	void setIllgalPair(char a, char b);

	bool isIllgalPair(char a, char b);
private:
	char*  illgalPair;
	int    size;
};