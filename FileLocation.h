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
		static std::wstring TXT_EXTENSION;
		static std::wstring PNG_EXTENSION;
		static std::wstring VS_SHADER_EXTENSION;
		static std::wstring FS_SHADER_EXTENSION;

		FileLocation(const FileDirectory* PARENT_DIRECTORY, const std::wstring FILE_NAME, const std::wstring FILE_EXTENSION);
		~FileLocation();

		std::wstring getFileName() const;
		const std::wstring& getFileNameNoExtension() const;
		std::wstring getFullPath() const;

		const FileDirectory& getParentDirectory() const;

		void setCreated(GLboolean isCreated);
		const GLboolean& isCreated() const;

		GLboolean createFile(std::ofstream& fileWriter);

	private:
		static Logger logger;
		GLboolean mIsCreated;

		const std::wstring mFILE_NAME;
		const std::wstring mFILE_EXTENSION;
		const FileDirectory* mPARENT_DIRECTORY;
	};
}

#endif