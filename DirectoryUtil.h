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

		//Appdata
		const FileDirectory* const mAPPDATA;		//Appdata directory
		const FileDirectory* const mUSER_CONFIG;	//Top level user config directory
		const FileDirectory* const mUSER_LOGGER;	//User logger settings

		//Executable
		const FileDirectory* const mEXE_ROOT;		//Root directory
		const FileDirectory* const mEXE_BIN;		//For dlls
		const FileDirectory* const mEXE_RESOURCES;	//Top level resource directory
		const FileDirectory* const mEXE_ASSETS;		//Top level image assets

		virtual ~DirectoryUtil();

	private:
		static Logger logger;

		static FileDirectory* createDirectory(const GUID& folderId, const std::wstring& dirName, GLboolean isPathRelative);
		static FileDirectory* createDirectory(const std::wstring& foldPath, const std::wstring& dirName, GLboolean isPathRelative);

		DirectoryUtil();
	};
}

#endif