#include "FileDirectory.h"
#include <iostream>

namespace Bountive
{
	FileDirectory::FileDirectory(std::string filePath) :
		mFILE_PATH(filePath)
	{

	}


	FileDirectory::~FileDirectory()
	{
		std::cout << "Deleting File Directory: \'" << mFILE_PATH << "\'." << std::endl;
	}
}