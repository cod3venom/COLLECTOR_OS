 
#pragma once

/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 12:25:01
*/

#ifndef __LOCALCONFIG_H__
#include <iostream>
#include "../FileSystem/fSys.h"
#include "../Config/Context.h";

class LocalConfig
{
	private:
		Context* ctx = nullptr;
		fSys fsys;
	public:
		LocalConfig(Context *ctx);
		~LocalConfig();
		bool readConfig();
};

#endif // __LOCALCONFIG_H__

