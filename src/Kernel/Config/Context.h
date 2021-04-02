/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#pragma once
#ifndef CONTEXT_H
#include <iostream>
#include "Constants.h"

#include "../GUI/MainMenu.h"
class MainMenu;
class Context
{
	private:
		Constants* constants = nullptr;
		MainMenu* mainMenu = nullptr;
		
	public:
		Context();
		~Context();

		void setConstants(Constants *constants);
		Constants* getConstants();

		void setMainMenu(MainMenu* mainMenu);
		MainMenu* getMainMenu();
};

#endif // CONTEXT_H

