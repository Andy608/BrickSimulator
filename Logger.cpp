#include "Logger.h"

namespace Bountive
{
	Logger::Logger(std::string loggerName, const Level& minimumLoggerLevel) :
		mLoggerName(loggerName),
		mMinimumLoggerLevel(minimumLoggerLevel),
		mLogger(log4cxx::LoggerPtr(log4cxx::Logger::getLogger(mLoggerName)))
	{
		log(Level::LEVEL_TRACE, "Initializing Logger: " + mLoggerName);
	}


	Logger::~Logger()
	{
		log(Level::LEVEL_TRACE, "Deleting Logger: " + mLoggerName);
	}


	void Logger::setMinimumLevel(const Level& minimumLogLevel)
	{
		mMinimumLoggerLevel = minimumLogLevel;
		switch(mMinimumLoggerLevel)
		{
		case Level::LEVEL_ALL:
			mLogger->setLevel(log4cxx::Level::getAll());
			break;
		case Level::LEVEL_TRACE:
			mLogger->setLevel(log4cxx::Level::getTrace());
			break;
		case Level::LEVEL_DEBUG:
			mLogger->setLevel(log4cxx::Level::getDebug());
			break;
		case Level::LEVEL_WARN:
			mLogger->setLevel(log4cxx::Level::getWarn());
			break;
		case Level::LEVEL_ERROR:
			mLogger->setLevel(log4cxx::Level::getError());
			break;
		case Level::LEVEL_FATAL:
			mLogger->setLevel(log4cxx::Level::getFatal());
			break;
		default:
			mLogger->setLevel(log4cxx::Level::getInfo());
			break;
		}
	}


	void Logger::log(const Level& messageLevel, std::wstring message) const
	{
		switch (messageLevel)
		{
		case Level::LEVEL_TRACE:
			LOG4CXX_TRACE(mLogger, message);
			break;
		case Level::LEVEL_DEBUG:
			LOG4CXX_DEBUG(mLogger, message);
			break;
		case Level::LEVEL_WARN:
			LOG4CXX_WARN(mLogger, message);
			break;
		case Level::LEVEL_ERROR:
			LOG4CXX_ERROR(mLogger, message);
			break;
		case Level::LEVEL_FATAL:
			LOG4CXX_FATAL(mLogger, message);
			break;
		default:
			LOG4CXX_INFO(mLogger, message);
			break;
		}
	}


	void Logger::log(const Level& messageLevel, std::string message) const
	{
		switch (messageLevel)
		{
		case Level::LEVEL_TRACE:
			LOG4CXX_TRACE(mLogger, message);
			break;
		case Level::LEVEL_DEBUG:
			LOG4CXX_DEBUG(mLogger, message);
			break;
		case Level::LEVEL_WARN:
			LOG4CXX_WARN(mLogger, message);
			break;
		case Level::LEVEL_ERROR:
			LOG4CXX_ERROR(mLogger, message);
			break;
		case Level::LEVEL_FATAL:
			LOG4CXX_FATAL(mLogger, message);
			break;
		default:
			LOG4CXX_INFO(mLogger, message);
			break;
		}
	}


	const std::string& Logger::getName() const
	{
		return mLoggerName;
	}


	const Logger::Level& Logger::getMinimumLevel() const
	{
		return mMinimumLoggerLevel;
	}
}