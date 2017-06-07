#include "FileReader.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileReader::logger = Logger("FileReader", Logger::Level::LEVEL_ALL);

	FileReader::FileReader() :
		mReadStream(new std::ifstream())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating FileReader...");
	}


	FileReader::~FileReader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting FileReader...");
		delete mReadStream;
	}


	void FileReader::getFileContents(const FileLocation& FILE, std::string& fileContents)
	{
		try
		{
			mReadStream->open(FILE.getFullPath(), std::ifstream::in);

			if (mReadStream->is_open())
			{
				std::stringstream stream;

				stream << mReadStream->rdbuf();
			
				fileContents = stream.str();
			}
			else
			{
				throw std::wstring(L"Unable to read file: " + FILE.getFullPath());
			}
		}
		catch (std::wstring e)
		{
			logger.log(Logger::Level::LEVEL_ERROR, e);
		}

		mReadStream->close();
	}


	std::vector<std::string> FileReader::getLinesInFile(const FileLocation& FILE)
	{
		std::vector<std::string> lines = std::vector<std::string>();
		std::string line;

		mReadStream->open(FILE.getFullPath(), std::wifstream::in);

		if (mReadStream->is_open())
		{
			while (std::getline(*mReadStream, line))
			{
				lines.push_back(line);
			}
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Unable to read file.");
		}

		mReadStream->close();
		return lines;
	}


	std::ifstream* FileReader::getReadStream() const
	{
		return mReadStream;
	}
}