#include <glew.h>
#include <Windows.h>
#include "FileDirectory.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileDirectory::logger = Logger("FileDirectory", Logger::Level::LEVEL_ALL);

	FileDirectory::FileDirectory(std::wstring filePath, std::wstring folderName, GLboolean isPathRelative) :
		mFILE_PATH(filePath), 
		mFOLDER_NAME(folderName),
		mPATH_RELATIVE(isPathRelative)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating File Directory: \'" + getDirectory() + L"\'.");
	}


	FileDirectory::~FileDirectory()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting File Directory: \'" + getDirectory() + L"\'.");
	}


	std::wstring FileDirectory::getDirectory() const
	{
		if (mFILE_PATH.length() > 0)
		{
			return mFILE_PATH + L"\\" + mFOLDER_NAME;
		}
		else
		{
			return mFOLDER_NAME;
		}
	}


	const std::wstring& FileDirectory::getParentDirectory() const
	{
		return mFILE_PATH;
	}


	const std::wstring& FileDirectory::getFolderName() const
	{
		return mFOLDER_NAME;
	}


	const GLboolean& FileDirectory::isPathRelative() const
	{
		return mPATH_RELATIVE;
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