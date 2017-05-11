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
		FileDirectory(std::wstring filePath);
		~FileDirectory();

		std::wstring getDirectory() const;
		GLboolean createDirectory() const;

	private:
		const std::wstring mFILE_PATH;
	};
}

#endif