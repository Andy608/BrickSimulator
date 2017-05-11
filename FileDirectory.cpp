#include "FileDirectory.h"
#include <glew.h>
#include <iostream>
#include <Windows.h>

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


	void FileDirectory::printDirectory() const
	{
		std::wcout << "Directory: " << mFILE_PATH << std::endl;
	}


	bool FileDirectory::createDirectory()
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