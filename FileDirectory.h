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
		FileDirectory(std::wstring filePath, std::wstring folderName, GLboolean isPathRelative);
		~FileDirectory();

		std::wstring getDirectory() const;
		const std::wstring& getParentDirectory() const;
		const std::wstring& getFolderName() const;

		const GLboolean& isPathRelative() const;

		GLboolean createDirectory() const;
		operator std::wstring() const;

	private:
		static Logger logger;

		const std::wstring mFILE_PATH;
		const std::wstring mFOLDER_NAME;
		const GLboolean mPATH_RELATIVE;
	};
}

#endif