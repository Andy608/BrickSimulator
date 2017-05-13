#include "FileWriter.h"
#include <iostream>

namespace Bountive
{
	FileWriter::FileWriter() :
		mWriteStream(new std::wofstream())
	{

	}


	FileWriter::~FileWriter() 
	{
		std::wcout << "Deleting FileWriter." << std::endl;
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
			std::wcout << "Writing to file: " << file.getFullPath() << std::endl;

			if (lines.size() > 0)
			{
				*mWriteStream << lines.at(0);

				for (GLuint i = 1; i < lines.size(); ++i)
				{
					*mWriteStream << std::endl << lines.at(i);
				}
			}

			mWriteStream->close();
			return true;
		}
		else
		{
			std::wcout << "Error writing to file: " << file.getFullPath() << std::endl;
			mWriteStream->close();
			return false;
		}
	}
}