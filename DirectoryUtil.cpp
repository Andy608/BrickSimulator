#include <iostream>
#include <sstream>
#include "DirectoryUtil.h"

namespace Bountive
{
	DirectoryUtil* DirectoryUtil::instance = nullptr;

	const FileDirectory* DirectoryUtil::APPDATA_DIRECTORY = nullptr;

	DirectoryUtil* DirectoryUtil::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new DirectoryUtil();
				APPDATA_DIRECTORY = createDirectory(FOLDERID_RoamingAppData, L"Brick Simulator");
				std::wcout << APPDATA_DIRECTORY->getDirectory() << std::endl;
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


	const FileDirectory* const DirectoryUtil::getmAppdataDir()
	{
		return APPDATA_DIRECTORY;
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


	FileDirectory* DirectoryUtil::createDirectory(const std::wstring &folderPath, const std::wstring& dirName)
	{
		FileDirectory* dir = new FileDirectory(folderPath, dirName);
		dir->createDirectory();
		return dir;
	}


	DirectoryUtil::DirectoryUtil() {}


	DirectoryUtil::~DirectoryUtil()
	{
		std::cout << "Deleting DirectoryUtil." << std::endl;
		delete APPDATA_DIRECTORY;
	}
}