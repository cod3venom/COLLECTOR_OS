/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#pragma once
#ifndef __BOOTLOADER_H__
#include <iostream>
#include <map>
#include "../Config/Context.h"
#include "../GUI/MainMenu.h"
class BootLoader
{
	private:
		CNeatWnd* mainWindow;
		Context* ctx = new Context();
		MainMenu* mainMenu;
		bool InitializeMainMenu();
	public:
		BootLoader(CNeatWnd* mainWindow);
		~BootLoader();

		void Load();
};

#endif // __BOOTLOADER_H__

