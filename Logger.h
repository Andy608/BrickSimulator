#pragma once
#ifndef BOUNTIVE_LOGGER_H_
#define BOUNTIVE_LOGGER_H_

#include <glew.h>
#include <string>
#include <log4cxx\logger.h>

namespace Bountive
{
	class Logger
	{
	public:
		enum class Level : GLint
		{
			LEVEL_ALL,
			LEVEL_TRACE,
			LEVEL_DEBUG,
			LEVEL_INFO,
			LEVEL_WARN,
			LEVEL_ERROR,
			LEVEL_FATAL
		};

		Logger(std::string loggerName, const Level& minimumLogLevel);
		~Logger();

		void setMinimumLevel(const Level& minimumLogLevel);
		void log(const Level& messageLevel, std::wstring message) const;
		void log(const Level& messageLevel, std::string message) const;

		const std::string& getName() const;
		const Level& getMinimumLevel() const;

	private:
		std::string mLoggerName;
		Level mMinimumLoggerLevel;
		log4cxx::LoggerPtr mLogger;
	};
}

#endif