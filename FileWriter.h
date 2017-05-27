#pragma once
#ifndef BOUNTIVE_FILEWRITER_H_
#define BOUNTIVE_FILEWRITER_H_

#include <glew.h>
#include <fstream>
#include <vector>
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class FileWriter
	{
	public:
		FileWriter();
		~FileWriter();

		std::ofstream& getWriteStream() const;
		GLboolean writeLinesInFile(const FileLocation& file, const std::vector<std::string>& lines);

	private:
		static Logger logger;
		std::ofstream* mWriteStream;
	};
}

#endif