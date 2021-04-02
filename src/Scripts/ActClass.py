import os
import sys

header_template: str = """ 
#pragma once
#ifndef ^safeprojectname_H
#include <iostream>
#include "../../config/Context.h"

class safeprojectname
{
	private:
		Context* ctx;
	public:
		safeprojectname(Context* ctx);
		~safeprojectname();
		void Analyse();
};

#endif // ^safeprojectname_H

"""
cpp_template: str = """ 
#include "safeprojectname.h"

"""
class_name = sys.argv[1]

IFDEF_NAME: str = "^safeprojectname"
NEW_CLASS_NAME = "safeprojectname"
fullClass = header_template.replace(IFDEF_NAME, class_name.upper()).replace(NEW_CLASS_NAME, class_name)
fullCpp = cpp_template.replace(NEW_CLASS_NAME, class_name)

print(fullClass)
print(fullCpp)

with open(class_name+".h", "w") as headerWriter:
	headerWriter.write(fullClass);

with open(class_name+".cpp", "w") as cppWriter:
	cppWriter.write(fullCpp);