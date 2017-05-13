#pragma once
#ifndef BOUNTIVE_FILEUTIL
#define BOUNTIVE_FILEUTIL

#include "SettingsHandler.h"
#include <shlobj.h>
#include <glew.h>
#include <string>

namespace Bountive
{
	class FileUtil
	{
	public:
		static FileUtil* instance;
		static FileUtil* init();

		virtual ~FileUtil();

		static const FileDirectory* const getmAppdataDir();

		static FileDirectory* createDirectory(const GUID& folderId, const std::wstring& dirName);
		static FileDirectory* createDirectory(const std::wstring& foldPath, const std::wstring& dirName);

	private:
		static const SettingsHandler* SETTINGS_HANDLER;

		static const std::wstring APPDATA_FOLDER_NAME;
		static const FileDirectory* APPDATA_DIRECTORY;

		FileUtil();
	};
}

#endif