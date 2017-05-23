#include "FileLocation.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileLocation::logger = Logger("FileLocation", Logger::Level::LEVEL_ALL);
	std::wstring FileLocation::TXT_EXTENSION = L".txt";
	std::wstring FileLocation::PNG_EXTENSION = L".png";

	FileLocation::FileLocation(const FileDirectory* PARENT_DIRECTORY, const std::wstring FILE_NAME, const std::wstring FILE_EXTENSION) :
		mPARENT_DIRECTORY(PARENT_DIRECTORY),
		mFILE_NAME(FILE_NAME),
		mFILE_EXTENSION(FILE_EXTENSION),
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


	const FileDirectory& FileLocation::getParentDirectory() const
	{
		return *mPARENT_DIRECTORY;
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