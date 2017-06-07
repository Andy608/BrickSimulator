#pragma once
#ifndef BOUNTIVE_FILEREADER_H_
#define BOUNTIVE_FILEREADER_H_

#include <fstream>
#include <vector>
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class FileReader
	{
	public:
		FileReader();
		~FileReader();

		void getFileContents(const FileLocation& FILE, std::string& fileContents);
		std::vector<std::string> getLinesInFile(const FileLocation& FILE);

		std::ifstream* getReadStream() const;

	private:
		static Logger logger;
		std::ifstream* mReadStream;
	};
}

#endif