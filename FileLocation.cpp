#include "FileLocation.h"
#include <iostream>

namespace Bountive
{
	std::wfstream FileLocation::fileStream = std::wfstream();

	FileLocation::FileLocation(const FileDirectory* parentDirectory, const std::wstring fileName, const std::wstring fileExtension) :
		mPARENT_DIRECTORY(parentDirectory), mFILE_NAME(fileName), mFILE_EXTENSION(fileExtension)
	{
		
	}


	FileLocation::~FileLocation() {}


	std::wstring FileLocation::getFileName() const
	{
		return mFILE_NAME + mFILE_EXTENSION;
	}


	std::wstring FileLocation::getFileNameNoExtension() const
	{
		return mFILE_NAME;
	}


	std::wstring FileLocation::getFullPath() const
	{
		return mPARENT_DIRECTORY->getDirectory() + L"\\" + getFileName();
	}


	GLboolean FileLocation::createFile() const
	{
		fileStream.open(getFullPath(), 
			std::wfstream::in | std::wfstream::out | std::wfstream::trunc | std::wfstream::binary);

		if (fileStream.good())
		{
			std::wcout << "Creating file: " << getFullPath() << std::endl;
			fileStream << "YO YO YO";
			fileStream.close();
			return true;
		}
		else
		{
			std::wcout << "Error creating file: " << getFullPath() << std::endl;
			fileStream.close();
			return false;
		}
	}
}