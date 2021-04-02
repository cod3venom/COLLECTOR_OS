/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#pragma once
#ifndef __FSYS_H__
#include <iostream>
#include <fstream>
#include <string>
class fSys
{
	private:
	public:
		fSys();
		~fSys();
		bool isFile(std::string filePath);
		bool isDir(std::string dirPath);
		bool mkDir(std::string dirPath);
		std::string readFile(std::string fileName);
		bool writeFile(std::string filename, std::string input, bool append = false);

};

#endif // __FSYS_H__

