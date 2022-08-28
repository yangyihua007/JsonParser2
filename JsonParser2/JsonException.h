#pragma once

#include <iostream>

class JsonException: public std::exception
{
public:
	JsonException();
	~JsonException();
};