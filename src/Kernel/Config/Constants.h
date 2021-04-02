 
#pragma once
/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:41:49
*/

#ifndef __CONSTANTS_H__
#include <iostream>
 

class Constants
{
	private:
		struct structLocalConfig
		{
			std::string pBoot = "boot/";
			std::string pConfig = "boot/config/";
			std::string pLocalConfig = "boot/config/Config.VEN";
		};

	public:
		Constants();
		~Constants();
		structLocalConfig __LOCAL_CONFIG__;
		const std::string __EMPTY__ = "";
		
};

#endif // __CONSTANTS_H__

