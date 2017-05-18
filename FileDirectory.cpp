#include <glew.h>
#include <iostream>
#include <Windows.h>
#include "FileDirectory.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileDirectory::logger = Logger("FileDirectory", Logger::Level::LEVEL_ALL);

	FileDirectory::FileDirectory(std::wstring filePath, std::wstring folderName) :
		mFILE_PATH(filePath), 
		mFOLDER_NAME(folderName)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating File Directory: \'" + getDirectory() + L"\'.");
	}


	FileDirectory::~FileDirectory()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting File Directory: \'" + getDirectory() + L"\'.");
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
				logger.log(Logger::Level::LEVEL_DEBUG, L"Valid directory at: \'" + getDirectory() + L"\'.");
				return GL_TRUE;
			}
			else
			{
				throw(std::wstring(L"Could not create directory with path: \'" + getDirectory() + L"\'."));
			}
		}
		catch (std::wstring e)
		{
			logger.log(Logger::Level::LEVEL_FATAL, e);
			return GL_FALSE;
		}
	}


	FileDirectory::operator std::wstring() const
	{
		return mFILE_PATH;
	}
}