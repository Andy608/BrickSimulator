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
				logger.log(Logger::Level::LEVEL_FATAL, L"Could not initialize DirectoryUtil. Error: " + e);
			}
		}

		return instance;
	}


	FileDirectory* DirectoryUtil::createDirectory(const GUID& folderId, const std::wstring& dirName, GLboolean isPathRelative)
	{
		FileDirectory* dir = nullptr;

		wchar_t* path = nullptr;
		HRESULT result = SHGetKnownFolderPath(folderId, NULL, NULL, &path);

		if (SUCCEEDED(result))
		{
			std::wstringstream pathDir;
			pathDir << path;
			dir = new FileDirectory(pathDir.str(), dirName, isPathRelative);

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


	FileDirectory* DirectoryUtil::createDirectory(const std::wstring &folderPath, const std::wstring& dirName, GLboolean isPathRelative)
	{
		FileDirectory* dir = new FileDirectory(folderPath, dirName, isPathRelative);
		dir->createDirectory();
		return dir;
	}


	DirectoryUtil::DirectoryUtil() 
	try : 
		mAPPDATA(createDirectory(FOLDERID_RoamingAppData, L"Brick Simulator", GL_FALSE)),
		mUSER_CONFIG(createDirectory(mAPPDATA->getDirectory(), L"config", GL_FALSE)),
		mUSER_LOGGER(createDirectory(mAPPDATA->getDirectory(), L"logger", GL_FALSE)),
		
		mEXE_ROOT(new FileDirectory(L"", L"bountive", GL_TRUE)),
		mEXE_BIN(new FileDirectory(mEXE_ROOT->getDirectory(), L"bin", GL_TRUE)),
		mEXE_ASSETS(new FileDirectory(mEXE_ROOT->getDirectory(), L"assets", GL_TRUE)),
		mEXE_RESOURCES(new FileDirectory(mEXE_ROOT->getDirectory(), L"resources", GL_TRUE)),
		mEXE_IMAGES(new FileDirectory(mEXE_ASSETS->getDirectory(), L"images", GL_TRUE)),
		mEXE_SHADERS(new FileDirectory(mEXE_ASSETS->getDirectory(), L"shaders", GL_TRUE))
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
		
		delete mUSER_CONFIG;
		delete mUSER_LOGGER;
		delete mAPPDATA;

		delete mEXE_BIN;
		delete mEXE_ASSETS;
		delete mEXE_RESOURCES;
		delete mEXE_ROOT;
		delete mEXE_IMAGES;
		delete mEXE_SHADERS;
	}
}