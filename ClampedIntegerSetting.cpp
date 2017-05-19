#include "ClampedIntegerSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger ClampedIntegerSetting::logger = Logger("ClampedIntegerSetting", Logger::Level::LEVEL_ALL);

	ClampedIntegerSetting::ClampedIntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER, const GLint MIN_INTEGER, const GLint MAX_INTEGER) :
		IntegerSetting(settingName, DEFAULT_INTEGER),
		mMIN_INTEGER(MIN_INTEGER),
		mMAX_INTEGER(MAX_INTEGER)
	{
		logger.log(Logger::Level::LEVEL_TRACE, L"Creating ClampedIntegerSetting: " + mSettingName);
	}


	ClampedIntegerSetting::~ClampedIntegerSetting() 
	{
		logger.log(Logger::Level::LEVEL_TRACE, L"Creating ClampedIntegerSetting: " + mSettingName);
	}


	void ClampedIntegerSetting::setCustomInteger(GLint customInteger)
	{
		mCustomInteger = clamp(customInteger);
		logger.log(Logger::Level::LEVEL_TRACE, L"ClampedIntegerSetting: " + mSettingName + L" Default: " +
			toString(mDEFAULT_INTEGER) + L" Custom: " + toString(mCustomInteger) + 
			L" MIN/MAX: [" + std::to_wstring(mMIN_INTEGER) + L", " + std::to_wstring(mMAX_INTEGER) + L"]");
	}


	const GLint& ClampedIntegerSetting::getMinInteger() const
	{
		return mMIN_INTEGER;
	}


	const GLint& ClampedIntegerSetting::getMaxInteger() const
	{
		return mMAX_INTEGER;
	}


	GLint& ClampedIntegerSetting::clamp(GLint& customInteger) const
	{
		if (customInteger > mMAX_INTEGER)
		{
			customInteger = mMAX_INTEGER;
			logger.log(Logger::Level::LEVEL_WARN, "Custom integer value: " + 
				std::to_string(customInteger) + " cannot be greater than max integer value: " +
				std::to_string(mMAX_INTEGER) + ". Setting to max value.");
		}
		else if (customInteger < mMIN_INTEGER)
		{
			customInteger = mMIN_INTEGER;
			logger.log(Logger::Level::LEVEL_WARN, "Custom integer value: " +
				std::to_string(customInteger) + " cannot be less than min integer value: " +
				std::to_string(mMIN_INTEGER) + ". Setting to min value.");
		}

		return customInteger;
	}
}