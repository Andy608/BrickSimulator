#pragma once
#ifndef BOUNTIVE_FILEUTIL
#define BOUNTIVE_FILEUTIL

#include "FileDirectory.h"
#include <glew.h>
#include <shlobj.h>
#include <string>

namespace Bountive
{
	class FileUtil
	{
	public:
		static FileUtil* instance;
		static FileUtil* init();

		virtual ~FileUtil();

		const FileDirectory* const getmAppdataDir() const;

	protected:
		const std::wstring BRICKSIMULATOR_APPDATA_FOLDER_NAME = L"Brick Simulator";
		FileDirectory* mAppdataDir;

		FileUtil();

		FileDirectory* createDirectory(const GUID folderId, std::wstring dirName);
	};
}

#endif