#include <log4cxx\helpers\exception.h>
#include <log4cxx\basicconfigurator.h>
#include "LoggerUtil.h"
#include "Logger.h"
#include "FileDirectory.h"
#include "DirectoryUtil.h"

namespace Bountive
{
	LoggerUtil* LoggerUtil::instance = nullptr;
	Logger LoggerUtil::logger = Logger("LoggerUtil", Logger::Level::LEVEL_ALL);
	const std::wstring LoggerUtil::CONSOLE_HEADING = L"[%5p] (%c.cpp:%L) T%r - %m%n";
	const std::wstring LoggerUtil::FILE_HEADING = L"%d{MM/dd/yyyy} %d{%I:%M:%S} [%5p | Thread: %t] (%c.cpp:%L) T%r	- %m%n";
	GLboolean LoggerUtil::isConsoleAppender = GL_FALSE;
	GLboolean LoggerUtil::isFileAppender = GL_FALSE;

	LoggerUtil* LoggerUtil::init()
	{
		if (instance == nullptr)
		{
			instance = new LoggerUtil();
			log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getDebug());
		}

		return instance;
	}


	void LoggerUtil::initConsoleAppender()
	{
		if (!isConsoleAppender)
		{
			log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(instance->mConsoleAppender));
			instance->mConsoleAppender = new log4cxx::ConsoleAppender(instance->mConsoleLayout);
			log4cxx::Logger::getRootLogger()->addAppender(instance->mConsoleAppender);
			logger.log(Logger::Level::LEVEL_DEBUG, "LoggerUtil is successfully initialized for console logging!");
			isConsoleAppender = GL_TRUE;
		}
	}


	void LoggerUtil::initFileAppender()
	{
		if (!isFileAppender)
		{
			try
			{
				instance->mLOGGER_DIRECTORY = DirectoryUtil::instance->mUSER_LOGGER;
				instance->mLOG_FILE = new FileLocation(instance->mLOGGER_DIRECTORY, L"log_report", FileLocation::TXT_EXTENSION);
				instance->mFileAppender = new log4cxx::FileAppender(instance->mFileLayout, instance->mLOG_FILE->getFullPath(), GL_FALSE);

				instance->mFileAppender->activateOptions(instance->mLoggerPool);

				log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(instance->mFileAppender));
				log4cxx::Logger::getRootLogger()->addAppender(instance->mFileAppender);
			}
			catch (log4cxx::helpers::Exception& e)
			{
				throw(e);
			}

			logger.log(Logger::Level::LEVEL_DEBUG, "LoggerUtil is successfully initialized for file logging!");
			isFileAppender = GL_TRUE;
		}
	}


	LoggerUtil::LoggerUtil()
	try :
		mLOGGER_DIRECTORY(nullptr),
		mLOG_FILE(nullptr),
		mConsoleLayout(new log4cxx::PatternLayout(CONSOLE_HEADING)),
		mFileLayout(new log4cxx::PatternLayout(FILE_HEADING)),
		mConsoleAppender(nullptr),
		mFileAppender(nullptr),
		mLoggerPool()
	{
		
	}
	catch (log4cxx::helpers::Exception& e)
	{
		throw(e);
	}


	LoggerUtil::~LoggerUtil()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting LoggerUtil...");
		delete mLOG_FILE;
	}
}