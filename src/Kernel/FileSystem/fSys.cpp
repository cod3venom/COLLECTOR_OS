 
#include "fSys.h"



fSys::fSys()
{
}

fSys::~fSys()
{
}

bool fSys::isFile(std::string filePath)
{
	std::ifstream fin(filePath);
	bool flag = fin.is_open() ? true : false;
	std::cout << std::to_string(flag) << std::endl;
	return flag;
}

bool fSys::isDir(std::string dirPath)
{
	return false;
}

bool fSys::mkDir(std::string dirPath)
{
	return false;
}

std::string fSys::readFile(std::string fileName)
{
	return std::string();
}

bool fSys::writeFile(std::string filename, std::string input, bool append)
{
	return false;
}
