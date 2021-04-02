 
#include "MainMenu.h"
/// <summary>
/// 
/// </summary>
/// <param name="ctx"></param>
/// <param name="mainWindow"></param>
MainMenu::MainMenu(Context *ctx,CNeatWnd *mainWindow) : CNeatMenuView()
{
	this->ctx = ctx;
	this->mainWindow = mainWindow;
}

/// <summary>
/// 
/// </summary>
MainMenu::~MainMenu()
{
}

 
/// <summary>
/// 
/// </summary>
/// <param name="menuItems"></param>
void MainMenu::setMenuItems(std::map<std::string, int> *menuItems)
{
	this->menuItems = menuItems;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::map<std::string, int> *MainMenu::getMenuItems()
{
	return this->menuItems;
}
 
/// <summary>
/// 
/// </summary>
/// <param name="pMenuTitle"></param>
void MainMenu::createMenu(std::string pMenuTitle)
{
	this->Create("", WS_CAPTION | WS_VISIBLE, 0, 0, 160, 160, this->mainWindow, WS_EX_NOCLOSEBOX);
	this->mainMenu->SetText(pMenuTitle);
	std::map<std::string, int>::iterator item;
	for (item = this->menuItems->begin(); item != this->menuItems->end(); item++)
	{
		if (item->first != this->ctx->getConstants()->__EMPTY__ && item->second >= 0)
		{
			this->mainMenu->AddMenuItem(item->first, item->second);
		 }
	}
	this->SetMenu(this->mainMenu);
	this->Invalidate();
}

bool MainMenu::showMainMenu()
{
	
	return false;
}

bool MainMenu::hideMainMenu()
{
	return false;
}

int MainMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{ 
	this->selectSuitableItem(nChar, nRepCnt, nFlags); 
	return 0;
}

int MainMenu::selectSuitableItem(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	std::cout << "ENTERD nChar : " << nChar << std::endl;
	std::cout << "ENTERD nRepCnt : " << nRepCnt << std::endl;
	std::cout << "ENTERD nFlags : " << nFlags << std::endl;
	
	return 0;
}


