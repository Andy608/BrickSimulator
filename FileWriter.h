#pragma once
#ifndef BOUNTIVE_FILEWRITER_H_
#define BOUNTIVE_FILEWRITER_H_

#include "FileLocation.h"
#include <fstream>
#include <glew.h>
#include <vector>

namespace Bountive
{
	class FileWriter
	{
	public:
		FileWriter();
		~FileWriter();

		std::wofstream& getWriteStream() const;
		GLboolean writeLinesInFile(const FileLocation& file, const std::vector<std::wstring>& lines);

	private:
		std::wofstream* mWriteStream;
	};
}

#endif