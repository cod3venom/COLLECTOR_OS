import os
import sys
import datetime
timeNow = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
header_template: str = """ 
#pragma once
/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : """ + str(timeNow)+  """
*/

#ifndef __^safeprojectname_H__
#include <iostream>
 

class safeprojectname
{
	private:
	public:
		safeprojectname();
		~safeprojectname();
};

#endif // __^safeprojectname_H__

"""
cpp_template: str = """ 
#include "safeprojectname.h"

"""
class_name = sys.argv[1]
path = sys.argv[2]

IFDEF_NAME: str = "^safeprojectname"
NEW_CLASS_NAME = "safeprojectname"
fullClass = header_template.replace(IFDEF_NAME, class_name.upper()).replace(NEW_CLASS_NAME, class_name)
fullCpp = cpp_template.replace(NEW_CLASS_NAME, class_name)

print(fullClass)
print(fullCpp)

with open(path + "\\"+class_name+".h", "w") as headerWriter:
	headerWriter.write(fullClass);

with open(path + "\\"+class_name+".cpp", "w") as cppWriter:
	cppWriter.write(fullCpp);
