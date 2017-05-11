#include "FileDirectory.h"
#include <iostream>
#include <Windows.h>
#include <glew.h>

namespace Bountive
{
	FileDirectory::FileDirectory(std::wstring filePath) :
		mFILE_PATH(filePath)
	{

	}


	FileDirectory::~FileDirectory()
	{
		std::wcout << "Deleting File Directory: \'" << mFILE_PATH << "\'." << std::endl;
	}


	std::wstring FileDirectory::getDirectory() const
	{
		return mFILE_PATH;
	}


	GLboolean FileDirectory::createDirectory() const
	{
		try
		{
			if (CreateDirectoryW(mFILE_PATH.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{
				return true;
			}
			else
			{
				throw(std::wstring(L"Could not create directory with path: " + mFILE_PATH));
			}
		}
		catch (std::wstring e)
		{
			std::wcout << e << std::endl;
			return false;
		}
	}
}