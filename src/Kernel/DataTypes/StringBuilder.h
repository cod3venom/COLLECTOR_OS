 
#pragma once

/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 12:02:13
*/

#ifndef __STRINGBUILDER_H__
#include <iostream>
#include "../Config/Constants.h"
 

class StringBuilder
{
	private:
		Constants *constants = new Constants();
		std::string fullData;
	public:
		StringBuilder();
		~StringBuilder();
		void append(std::string data, std::string delimiter = "");
		void addDelimiter(std::string delimiter);
		void clear();
		std::string __STR__(bool trim_on_last = false);
};

#endif // __STRINGBUILDER_H__

