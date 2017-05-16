#include <glew.h>
#include <iostream>
#include <Windows.h>
#include "FileDirectory.h"

namespace Bountive
{
	FileDirectory::FileDirectory(std::wstring filePath, std::wstring folderName) :
		mFILE_PATH(filePath), 
		mFOLDER_NAME(folderName)
	{

	}


	FileDirectory::~FileDirectory()
	{
		std::wcout << "Deleting File Directory: \'" << mFILE_PATH << L"\\" << mFOLDER_NAME << "\'." << std::endl;
	}


	std::wstring FileDirectory::getDirectory() const
	{
		return mFILE_PATH + L"\\" + mFOLDER_NAME;
	}


	std::wstring FileDirectory::getParentDirectory() const
	{
		return mFILE_PATH;
	}


	std::wstring FileDirectory::getFolderName() const
	{
		return mFOLDER_NAME;
	}


	GLboolean FileDirectory::createDirectory() const
	{
		try
		{
			if (CreateDirectoryW(getDirectory().c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{
				std::wcout << "Valid directory at: " << getDirectory() << std::endl;
				return GL_TRUE;
			}
			else
			{
				throw(std::wstring(L"Could not create directory with path: " + getDirectory()));
			}
		}
		catch (std::wstring e)
		{
			std::wcout << e << std::endl;
			return GL_FALSE;
		}
	}


	FileDirectory::operator std::wstring() const
	{
		return mFILE_PATH;
	}
}