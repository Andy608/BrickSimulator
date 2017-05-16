#pragma once
#ifndef BOUNTIVE_FILEREADER_H_
#define BOUNTIVE_FILEREADER_H_

#include <fstream>
#include <vector>
#include "FileLocation.h"

namespace Bountive
{
	class FileReader
	{
	public:
		FileReader();
		~FileReader();

		std::vector<std::wstring> getLinesInFile(const FileLocation& file);

	private:
		std::wifstream* mReadStream;
	};
}

#endif