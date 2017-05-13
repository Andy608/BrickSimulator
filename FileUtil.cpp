#include "FileUtil.h"
#include <iostream>
#include <sstream>

namespace Bountive
{
	FileUtil* FileUtil::instance = nullptr;

	const std::wstring FileUtil::APPDATA_FOLDER_NAME = L"Brick Simulator";

	const SettingsHandler* FileUtil::SETTINGS_HANDLER = nullptr;
	const FileDirectory* FileUtil::APPDATA_DIRECTORY = nullptr;

	FileUtil* FileUtil::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new FileUtil();
				APPDATA_DIRECTORY = createDirectory(FOLDERID_RoamingAppData, APPDATA_FOLDER_NAME);
				std::wcout << APPDATA_DIRECTORY->getDirectory() << std::endl;
				SETTINGS_HANDLER = SettingsHandler::init();
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


	const FileDirectory* const FileUtil::getmAppdataDir()
	{
		return APPDATA_DIRECTORY;
	}


	FileDirectory* FileUtil::createDirectory(const GUID& folderId, const std::wstring& dirName)
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
				throw (std::wstring(L"Could not create directory."));
			}
		}
		else
		{
			CoTaskMemFree(static_cast<void*>(path));
			throw (std::wstring(L"Could not find path with that GUID."));
		}

		CoTaskMemFree(static_cast<void*>(path));
		return dir;
	}


	FileDirectory* FileUtil::createDirectory(const std::wstring &folderPath, const std::wstring& dirName)
	{
		FileDirectory* dir = new FileDirectory(folderPath, dirName);
		dir->createDirectory();
		return dir;
	}


	FileUtil::FileUtil() {}


	FileUtil::~FileUtil()
	{
		std::cout << "Deleting FileUtil." << std::endl;
		delete APPDATA_DIRECTORY;
		delete SETTINGS_HANDLER;
	}
}