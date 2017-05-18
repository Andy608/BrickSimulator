#include <iostream>
#include <sstream>
#include "DirectoryUtil.h"
#include "Logger.h"

namespace Bountive
{
	DirectoryUtil* DirectoryUtil::instance = nullptr;
	Logger DirectoryUtil::logger = Logger("DirectoryUtil", Logger::Level::LEVEL_ALL);

	DirectoryUtil* DirectoryUtil::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new DirectoryUtil();
			}
			catch (std::wstring e)
			{
				delete instance;
				instance = nullptr;
				std::wcout << e << std::endl;
			}
		}

		return instance;
	}


	FileDirectory* DirectoryUtil::createDirectory(const GUID& folderId, const std::wstring& dirName)
	{
		FileDirectory* dir = nullptr;

		wchar_t* path = nullptr;
		HRESULT result = SHGetKnownFolderPath(folderId, NULL, NULL, &path);

		if (SUCCEEDED(result))
		{
			std::wstringstream pathDir;
			pathDir << path;
			dir = new FileDirectory(pathDir.str(), dirName);

			if (!dir->createDirectory())
			{
				std::wstring error = L"Could not create directory.";
				logger.log(Logger::Level::LEVEL_FATAL, error);
				throw (std::wstring(error));
			}
		}
		else
		{
			CoTaskMemFree(static_cast<void*>(path));
			std::wstring error = L"Could not find path with that GUID.";
			logger.log(Logger::Level::LEVEL_FATAL, error);
			throw (std::wstring(error));
		}

		CoTaskMemFree(static_cast<void*>(path));
		return dir;
	}


	FileDirectory* DirectoryUtil::createDirectory(const std::wstring &folderPath, const std::wstring& dirName)
	{
		FileDirectory* dir = new FileDirectory(folderPath, dirName);
		dir->createDirectory();
		return dir;
	}


	DirectoryUtil::DirectoryUtil() 
	try : 
		mAPPDATA_DIRECTORY(createDirectory(FOLDERID_RoamingAppData, L"Brick Simulator")),
		mSETTINGS_DIRECTORY(createDirectory(mAPPDATA_DIRECTORY->getDirectory(), L"settings")),
		mLOGGER_DIRECTORY(createDirectory(mAPPDATA_DIRECTORY->getDirectory(), L"logger"))
	{
		logger.log(Logger::Level::LEVEL_INFO, "Creating DirectoryUtil...");
	}
	catch (std::wstring e)
	{
		throw e;
	}


	DirectoryUtil::~DirectoryUtil()
	{
		logger.log(Logger::Level::LEVEL_INFO, "Deleting DirectoryUtil...");
		delete mAPPDATA_DIRECTORY;
		delete mSETTINGS_DIRECTORY;
		delete mLOGGER_DIRECTORY;
	}
}