
#include "JsonParser.h"
#include "JsonException.h"
#include <stdlib.h>    
int main()
{
	char*  jsonStr = "{\"  name  \":\"yangyihua\",\"age\":35,\"addressObj\":{\"address\":\"pengbu\",\"detail\":[{\"xueke\":\"yuwen\",\"score\":\"90\"},{\"xueke\":\"yingyu\",\"score\":\"92\"}]}}";
	try {
	    JsonParser*  parser = new JsonParser();
	    Object*  obj = parser->parse(jsonStr);
	    
	    obj->cout();
	    
	    delete obj;
	    delete parser;
	} catch(JsonException exception) {
		std::cout << "We catch a exception here" << std::endl;	
	}
	_CrtDumpMemoryLeaks();
	return 0;
}