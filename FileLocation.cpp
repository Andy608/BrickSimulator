#include "FileLocation.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileLocation::logger = Logger("FileLocation", Logger::Level::LEVEL_ALL);
	std::wstring FileLocation::TXT_EXT = L".txt";

	FileLocation::FileLocation(const FileDirectory* parentDirectory, const std::wstring fileName, const std::wstring fileExtension) :
		mPARENT_DIRECTORY(parentDirectory), 
		mFILE_NAME(fileName), 
		mFILE_EXTENSION(fileExtension),
		mIsCreated(GL_FALSE)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating FileLocation...");
	}


	FileLocation::~FileLocation() 
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting FileLocation...");
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
			logger.log(Logger::Level::LEVEL_DEBUG, L"Creating file: " + getFullPath());
			fileWriter.close();
			setCreated(GL_TRUE);
			return GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_FATAL, L"Error creating file: " + getFullPath());
			fileWriter.close();
			setCreated(GL_FALSE);
			return GL_FALSE;
		}
	}
}