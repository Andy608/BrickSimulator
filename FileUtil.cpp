#include "FileUtil.h"
#include <iostream>
#include <sstream>

namespace Bountive
{
	FileUtil* FileUtil::instance = nullptr;

	FileUtil* FileUtil::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new FileUtil();
			}
			catch (std::string e)
			{
				std::cout << e << std::endl;
			}
		}

		return instance;
	}

	
	FileUtil::FileUtil()
	try : mAPPDATA_DIRECTORY(createDirectory(FOLDERID_RoamingAppData, mAPPDATA_FOLDER_NAME))
	{
		
	}
	catch (std::string e)
	{
		throw (e);
	}


	FileUtil::~FileUtil()
	{
		std::cout << "Deleting FileUtil." << std::endl;
		delete mAPPDATA_DIRECTORY;
	}


	const FileDirectory* const FileUtil::getmAppdataDir() const
	{
		return mAPPDATA_DIRECTORY;
	}


	FileDirectory* FileUtil::createDirectory(const GUID folderId, std::wstring dirName)
	{
		FileDirectory* dir = nullptr;

		wchar_t* path = nullptr;
		HRESULT result = SHGetKnownFolderPath(folderId, NULL, NULL, &path);

		if (SUCCEEDED(result))
		{
			std::wstringstream ss;
			ss << path;
			std::wstring appdataPath = ss.str() + L"\\" + dirName;
			dir = new FileDirectory(appdataPath);

			if (!dir->createDirectory())
			{
				throw (std::string("Could not create directory."));
			}
		}
		else
		{
			CoTaskMemFree(static_cast<void*>(path));
			throw(std::string("Could not create path."));
		}

		CoTaskMemFree(static_cast<void*>(path));
		return dir;
	}
}