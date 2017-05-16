#pragma once
#ifndef BOUNTIVE_FILEWRITER_H_
#define BOUNTIVE_FILEWRITER_H_

#include <glew.h>
#include <fstream>
#include <vector>
#include "FileLocation.h"

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