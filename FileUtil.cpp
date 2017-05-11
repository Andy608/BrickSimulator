#include "FileUtil.h"
#include <iostream>

namespace Bountive
{
	FileUtil* FileUtil::instance = nullptr;

	FileUtil* FileUtil::init()
	{
		if (instance == nullptr)
		{
#if defined(_WIN32) || defined(_WIN64)
			instance = new WindowsFileUtil();
#elif __APPLE__
			instance = new MacFileUtil();
#elif __linux__

#endif
		}

		return instance;
	}

	
	FileUtil::FileUtil() :
		mAppdataDir(nullptr)
	{
		
	}


	FileUtil::~FileUtil()
	{
		std::cout << "Deleting FileUtil." << std::endl;
		delete mAppdataDir;
	}


	const FileDirectory* const FileUtil::getmAppdataDir() const
	{
		return mAppdataDir;
	}
}