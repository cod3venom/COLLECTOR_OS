#pragma once

/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 11:52:37
*/

#ifndef __LOGGER_H__
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime> 
#include "../DataTypes/StringBuilder.h"
#include "../Config/Constants.h"
class Logger
{
	private:
		StringBuilder st;
		Constants *constants = new Constants();
	public:
		Logger();
		~Logger();

		typedef enum
		{
			ERROR = 0,
			WARNING = 1,
			SUCCESS = 1
		};

		std::string dateNow();
		bool __PRINT__(std::string message, std::string caller = "");
};

#endif // __LOGGER_H__

