#include <iostream>
#include "FileReader.h"

namespace Bountive
{
	FileReader::FileReader() :
		mReadStream(new std::wifstream())
	{

	}


	FileReader::~FileReader()
	{
		std::wcout << "Deleting FileReader." << std::endl;
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