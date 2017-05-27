#include <stdexcept> 
#include "IntegerSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger IntegerSetting::logger = Logger("IntegerSetting", Logger::Level::LEVEL_ALL);

	IntegerSetting::IntegerSetting(std::string settingName, const GLint DEFAULT_INTEGER) :
		SettingType(settingName), 
		mDEFAULT_INTEGER(DEFAULT_INTEGER), 
		mCustomInteger(DEFAULT_INTEGER)
	{
		logger.log(Logger::Level::LEVEL_TRACE, "Creating IntegerSetting: " + mSettingName);
	}


	IntegerSetting::~IntegerSetting() 
	{
		logger.log(Logger::Level::LEVEL_TRACE, "Deleting IntegerSetting: " + mSettingName);
	}


	void IntegerSetting::setCustomInteger(GLint customInteger)
	{
		mCustomInteger = customInteger;
		logger.log(Logger::Level::LEVEL_TRACE, "IntegerSetting: " + mSettingName + " Default: " +
			toString(mDEFAULT_INTEGER) + " Custom: " + toString(mCustomInteger));
	}


	void IntegerSetting::setCustomInteger(std::string fileValue)
	{
		try
		{
			setCustomInteger(std::stoi(fileValue));
		}
		catch (const std::invalid_argument e)
		{
			logger.log(Logger::Level::LEVEL_WARN, "Could not convert \'" + fileValue + "\' to integer. Returning default value.");
			setCustomInteger(mDEFAULT_INTEGER);
		}
	}


	void IntegerSetting::operator=(GLint customInteger)
	{
		setCustomInteger(customInteger);
	}


	GLboolean IntegerSetting::operator==(GLint anotherInteger)
	{
		return (mCustomInteger == anotherInteger);
	}


	const GLint& IntegerSetting::getDefaultInteger() const
	{
		return mDEFAULT_INTEGER;
	}


	const GLint& IntegerSetting::getCustomInteger() const
	{
		return mCustomInteger;
	}


	GLboolean IntegerSetting::isModified() const
	{
		return (mDEFAULT_INTEGER != mCustomInteger);
	}


	std::string IntegerSetting::toString(GLint integerValue)
	{
		return std::to_string(integerValue);
	}


	std::string IntegerSetting::toFileString() const
	{
		return mSettingName + DELIMITER + toString(mCustomInteger);
	}


	void IntegerSetting::resetCustomValue()
	{
		mCustomInteger = mDEFAULT_INTEGER;
	}
}