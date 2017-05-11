#include "MacFileUtil.h"
#include <iostream>

namespace Bountive
{
	MacFileUtil::MacFileUtil() : 
		FileUtil()
	{
		mAppdataDir = new FileDirectory("Mac: ApplicationSupport Directoy");
	}


	MacFileUtil::~MacFileUtil()
	{
		std::cout << "Deleting MacFileUtil." << std::endl;
	}
}