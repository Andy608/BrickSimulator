#include "FileLocation.h"
#include <iostream>

namespace Bountive
{
	std::wstring FileLocation::TXT_EXT = L".txt";

	FileLocation::FileLocation(const FileDirectory* parentDirectory, const std::wstring fileName, const std::wstring fileExtension) :
		mPARENT_DIRECTORY(parentDirectory), 
		mFILE_NAME(fileName), 
		mFILE_EXTENSION(fileExtension),
		mIsCreated(false)
	{
		
	}


	FileLocation::~FileLocation() 
	{
		std::wcout << "Deleting FileLocation." << std::endl;
	}


	std::wstring FileLocation::getFileName() const
	{
		return mFILE_NAME + mFILE_EXTENSION;
	}


	const std::wstring& FileLocation::getFileNameNoExtension() const
	{
		return mFILE_NAME;
	}


	std::wstring FileLocation::getFullPath() const
	{
		return mPARENT_DIRECTORY->getDirectory() + L"\\" + getFileName();
	}


	const GLboolean& FileLocation::isCreated() const
	{
		return mIsCreated;
	}


	void FileLocation::setCreated(GLboolean isCreated)
	{
		mIsCreated = isCreated;
	}


	GLboolean FileLocation::createFile(std::wofstream& fileWriter)
	{
		fileWriter.open(getFullPath(), std::fstream::app);

		if (fileWriter.good())
		{
			std::wcout << "Creating file: " << getFullPath() << std::endl;
			fileWriter.close();
			setCreated(true);
			return true;
		}
		else
		{
			std::wcout << "Error creating file: " << getFullPath() << std::endl;
			fileWriter.close();
			setCreated(false);
			return false;
		}
	}
}