#pragma once
#ifndef BOUNTIVE_FILEDIRECTORY
#define BOUNTIVE_FILEDIRECTORY

#include <string>

namespace Bountive
{
	class FileDirectory
	{
	public:
		const std::string mFILE_PATH;

		FileDirectory(std::string filePath);
		~FileDirectory();
	};
}

#endif