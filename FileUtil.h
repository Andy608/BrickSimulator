#pragma once
#ifndef BOUNTIVE_FILEUTIL
#define BOUNTIVE_FILEUTIL

#include "FileDirectory.h"

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
		FileDirectory* mAppdataDir;

		FileUtil();
	};
}

#ifdef _WIN32
#include "WindowsFileUtil.h"
#ifdef _WIN64
#include "WindowsFileUtil.h"
#else
#endif
#elif __APPLE__
#if TARGET_OS_MAC
#include "MacFileUtil.h"
#else
#endif
#elif __linux__
#include "LinuxFileUtil.h"
#elif __unix__
#include "LinuxFileUtil.h"
#elif defined(_POST_VERSION)
#else
#endif

#endif