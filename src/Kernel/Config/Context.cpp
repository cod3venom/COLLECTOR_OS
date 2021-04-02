 
#include "Context.h"

Context::Context()
{
	this->constants = new Constants();
}

Context::~Context()
{
}

void Context::setConstants(Constants *constants)
{
	this->constants = constants;
}

Constants* Context::getConstants()
{
	return this->constants;
}

/// <summary>
/// Global main menu variable
/// </summary>
/// <param name="mainMenu"></param>
void Context::setMainMenu(MainMenu* mainMenu) { this->mainMenu = mainMenu; }
MainMenu* Context::getMainMenu() { return this->mainMenu; }
