#include <stdlib.h>    
#include <crtdbg.h> 
#include "grammar.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif

Grammar::Grammar()
{
	illgalPair = new char[MAX_ILLGALPAIR * 2];
	size = 0;
}
Grammar::~Grammar()
{
	delete [] illgalPair;
}
void Grammar::setIllgalPair(char a, char b)
{
	illgalPair[size] = a;
	illgalPair[size+1] = b;
	size+=2;
}

bool Grammar::isIllgalPair(char a, char b)
{
	bool bIllegal = false;
	for(int i = 0; i < size; i += 2) {
		if(*(illgalPair+i) == a && *(illgalPair+i+1) == b)
		{
			bIllegal = true;
			break;
		}
	}
	return bIllegal;
}
