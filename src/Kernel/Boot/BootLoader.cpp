 
#include "BootLoader.h"



BootLoader::BootLoader(CNeatWnd* mainWindow)
{
	this->mainMenu = new MainMenu(this->ctx, mainWindow);
	this->localConfig = new LocalConfig(this->ctx);
	this->ctx->setMainMenu(this->mainMenu);
}

BootLoader::~BootLoader()
{

}
bool BootLoader::readLocalConfig()
{
	bool flag = this->localConfig->readConfig();
	return flag;
}
void BootLoader::Load()
{
	this->readLocalConfig();
	this->InitializeMainMenu();
}

bool BootLoader::InitializeMainMenu()
{
	std::map<std::string, int> menuItems;
	menuItems.insert(std::make_pair("Scanner",0));
	menuItems.insert(std::make_pair("Show database", 1));
	menuItems.insert(std::make_pair("Export to PC", 2));
	menuItems.insert(std::make_pair("Bluetooth", 3));
	menuItems.insert(std::make_pair("WIFI", 4));
	menuItems.insert(std::make_pair("Recovery", 5));

	this->ctx->getMainMenu()->setMenuItems(&menuItems);
	this->ctx->getMainMenu()->createMenu();
	return true;
}


