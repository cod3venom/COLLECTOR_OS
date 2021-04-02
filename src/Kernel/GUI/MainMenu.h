 
#pragma once
/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 00:44:30
*/

#ifndef __MAINMENU_H__
#include <iostream>
#include <neatwin.h>
#include <neatctrl.h>
#include <map>
#include "../Config/Context.h"
#include "../Config/KeyBoard.h"

class Context;

class MainMenu : public CNeatMenuView
{
private:
	Context* ctx = nullptr;
	CNeatWnd *mainWindow = nullptr;
	CNeatMenu* mainMenu = new CNeatMenu;
	std::map<std::string, int> *menuItems;
		
public:
	MainMenu(Context* ctx, CNeatWnd* mainWindow);
	~MainMenu();
	void setMenuItems(std::map<std::string, int>* menuItems);
	std::map<std::string, int> *getMenuItems();
	 

 	void createMenu(std::string pMenuTitle = "Collector OS");
	bool showMainMenu();
	bool hideMainMenu();
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int selectSuitableItem(UINT nChar, UINT nRepCnt, UINT nFlags);
		
};

#endif // __MAINMENU_H__

