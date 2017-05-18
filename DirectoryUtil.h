#pragma once
#ifndef BOUNTIVE_DIRECTORYUTIL_H_
#define BOUNTIVE_DIRECTORYUTIL_H_

#include <glew.h>
#include <shlobj.h>
#include <string>
#include "FileDirectory.h"

namespace Bountive
{
	class Logger;

	class DirectoryUtil
	{
	public:
		static DirectoryUtil* instance;

		static DirectoryUtil* init();

		const FileDirectory* const mAPPDATA_DIRECTORY;
		const FileDirectory* const mSETTINGS_DIRECTORY;
		const FileDirectory* const mLOGGER_DIRECTORY;

		virtual ~DirectoryUtil();

	private:
		static Logger logger;

		static FileDirectory* createDirectory(const GUID& folderId, const std::wstring& dirName);
		static FileDirectory* createDirectory(const std::wstring& foldPath, const std::wstring& dirName);

		DirectoryUtil();
	};
}

#endif