#pragma once
#ifndef BOUNTIVE_FILELOCATION_H_
#define BOUNTIVE_FILELOCATION_H_

#include "FileDirectory.h"
#include <fstream>
#include <string>
#include <glew.h>

namespace Bountive
{
	class FileLocation
	{
	public:
		FileLocation(const FileDirectory* parentDirectory, const std::wstring fileName, const std::wstring fileExtension);
		~FileLocation();

		std::wstring getFileName() const;
		std::wstring getFileNameNoExtension() const;
		std::wstring getFullPath() const;

		GLboolean createFile() const;

	private:
		static std::wfstream fileStream;
		const std::wstring mFILE_NAME;
		const std::wstring mFILE_EXTENSION;
		const FileDirectory* mPARENT_DIRECTORY;
	};
}

#endif