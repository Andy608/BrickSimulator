#include "FileReader.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileReader::logger = Logger("FileReader", Logger::Level::LEVEL_ALL);

	FileReader::FileReader() :
		mReadStream(new std::wifstream())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating FileReader...");
	}


	FileReader::~FileReader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting FileReader...");
		delete mReadStream;
	}


	std::vector<std::wstring> FileReader::getLinesInFile(const FileLocation& file)
	{
		std::vector<std::wstring> lines = std::vector<std::wstring>();
		std::wstring line;

		mReadStream->open(file.getFullPath(), std::wifstream::in);

		if (mReadStream->is_open())
		{
			while (std::getline(*mReadStream, line))
			{
				lines.push_back(line);
			}
		}

		mReadStream->close();
		return lines;
	}
}