#pragma once
#ifndef BOUNTIVE_FILEDIRECTORY
#define BOUNTIVE_FILEDIRECTORY

#include <string>

namespace Bountive
{
	class FileDirectory
	{
	public:
		const std::wstring mFILE_PATH;

		FileDirectory(std::wstring filePath);
		~FileDirectory();

		void printDirectory() const;
		bool createDirectory();
	};
}

#endif