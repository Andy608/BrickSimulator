#pragma once
#ifndef BOUNTIVE_FILEDIRECTORY
#define BOUNTIVE_FILEDIRECTORY

#include <glew.h>
#include <string>

namespace Bountive
{
	class FileDirectory
	{
	public:
		FileDirectory(std::wstring filePath, std::wstring folderName);
		~FileDirectory();

		std::wstring getDirectory() const;
		std::wstring getDirectoryPath() const;
		std::wstring getFolderName() const;

		GLboolean createDirectory() const;
		operator std::wstring() const;

	private:
		const std::wstring mFILE_PATH;
		const std::wstring mFOLDER_NAME;
	};
}

#endif