#include <iostream>
#include "FileWriter.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileWriter::logger = Logger("FileWriter", Logger::Level::LEVEL_ALL);

	FileWriter::FileWriter() :
		mWriteStream(new std::wofstream())
	{
		logger.log(Logger::Level::LEVEL_ALL, "Creating FileWriter...");
	}


	FileWriter::~FileWriter() 
	{
		logger.log(Logger::Level::LEVEL_ALL, "Deleting FileWriter...");
		delete mWriteStream;
	}


	std::wofstream& FileWriter::getWriteStream() const
	{
		return *mWriteStream;
	}


	GLboolean FileWriter::writeLinesInFile(const FileLocation& file, const std::vector<std::wstring>& lines)
	{
		mWriteStream->open(file.getFullPath(), std::fstream::trunc);

		if (mWriteStream->good())
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Writing to file: " + file.getFullPath());

			if (lines.size() > 0)
			{
				*mWriteStream << lines.at(0);

				for (GLuint i = 1; i < lines.size(); ++i)
				{
					*mWriteStream << std::endl << lines.at(i);
				}
			}

			mWriteStream->close();
			return GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Error writing to file: " + file.getFullPath());
			mWriteStream->close();
			return GL_FALSE;
		}
	}
}