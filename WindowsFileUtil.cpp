#include "WindowsFileUtil.h"
#include <iostream>

namespace Bountive
{
	WindowsFileUtil::WindowsFileUtil() :
		FileUtil()
	{
		mAppdataDir = new FileDirectory("Windows: %Appdata% Directoy");
	}


	WindowsFileUtil::~WindowsFileUtil()
	{
		std::cout << "Deleting WindowsFileUtil." << std::endl;
	}
}