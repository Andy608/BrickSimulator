#pragma once
#ifndef BOUNTIVE_FILEDIRECTORY
#define BOUNTIVE_FILEDIRECTORY

#include <glew.h>
#include <string>

namespace Bountive
{
	class Logger;

	class FileDirectory
	{
	public:
		FileDirectory(std::wstring filePath, std::wstring folderName);
		~FileDirectory();

		std::wstring getDirectory() const;
		std::wstring getParentDirectory() const;
		std::wstring getFolderName() const;

		GLboolean createDirectory() const;
		operator std::wstring() const;

	private:
		static Logger logger;

		const std::wstring mFILE_PATH;
		const std::wstring mFOLDER_NAME;
	};
}

#endif