#pragma once
#ifndef BOUNTIVE_FILELOCATION_H_
#define BOUNTIVE_FILELOCATION_H_

#include <glew.h>
#include <fstream>
#include <string>
#include "FileDirectory.h"

namespace Bountive
{
	class Logger;

	class FileLocation
	{
	public:
		static std::wstring TXT_EXT;

		FileLocation(const FileDirectory* parentDirectory, const std::wstring fileName, const std::wstring fileExtension);
		~FileLocation();

		std::wstring getFileName() const;
		const std::wstring& getFileNameNoExtension() const;
		std::wstring getFullPath() const;

		void setCreated(GLboolean isCreated);
		const GLboolean& isCreated() const;

		GLboolean createFile(std::wofstream& fileWriter);

	private:
		static Logger logger;
		GLboolean mIsCreated;

		const std::wstring mFILE_NAME;
		const std::wstring mFILE_EXTENSION;
		const FileDirectory* mPARENT_DIRECTORY;
	};
}

#endif