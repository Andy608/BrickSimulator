#pragma once
#ifndef BOUNTIVE_FILEUTIL
#define BOUNTIVE_FILEUTIL

#include "FileDirectory.h"
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

		const FileDirectory* const getmAppdataDir() const;

	protected:
		const std::wstring mAPPDATA_FOLDER_NAME = L"Brick Simulator";
		const FileDirectory * const mAPPDATA_DIRECTORY;

		FileUtil();

		FileDirectory* createDirectory(const GUID folderId, std::wstring dirName);
	};
}

#endif