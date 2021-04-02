 
#include "StringBuilder.h"

StringBuilder::StringBuilder()
{
}

StringBuilder::~StringBuilder()
{
}

void StringBuilder::append(std::string data, std::string delimter)
{
	this->fullData += data;
}

void StringBuilder::addDelimiter(std::string delimiter)
{
	if (delimiter != this->constants->__EMPTY__)
	{
		this->fullData.append(delimiter + " ");
	}
}


void StringBuilder::clear()
{
	this->fullData = this->constants->__EMPTY__;
}

std::string StringBuilder::__STR__(bool trim_on_last)
{
	return  this->fullData.substr(0, this->fullData.size());
}

 