#pragma once
#ifndef BOUNTIVE_DIRECTORYUTIL_H_
#define BOUNTIVE_DIRECTORYUTIL_H_

#include "FileDirectory.h"
#include <shlobj.h>
#include <glew.h>
#include <string>

namespace Bountive
{
	class DirectoryUtil
	{
	public:
		static DirectoryUtil* instance;
		static DirectoryUtil* init();

		virtual ~DirectoryUtil();

		static const FileDirectory* const getmAppdataDir();

		static FileDirectory* createDirectory(const GUID& folderId, const std::wstring& dirName);
		static FileDirectory* createDirectory(const std::wstring& foldPath, const std::wstring& dirName);

	private:
		static const FileDirectory* APPDATA_DIRECTORY;

		DirectoryUtil();
	};
}

#endif