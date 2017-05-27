#include "BooleanSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger BooleanSetting::logger = Logger("BooleanSetting", Logger::Level::LEVEL_ALL);
	const std::string BooleanSetting::SETTING_TRUE = "true";
	const std::string BooleanSetting::SETTING_FALSE = "false";

	BooleanSetting::BooleanSetting(std::string settingName, const GLboolean DEFAULT_BOOLEAN) :
		SettingType(settingName), 
		mDEFAULT_BOOLEAN(DEFAULT_BOOLEAN), 
		mCustomBoolean(DEFAULT_BOOLEAN)
	{
		logger.log(Logger::Level::LEVEL_TRACE, "Creating BooleanSetting: " + mSettingName);
	}


	BooleanSetting::~BooleanSetting() 
	{
		logger.log(Logger::Level::LEVEL_TRACE, "Deleting BooleanSetting: " + mSettingName);
	}


	void BooleanSetting::setCustomBoolean(GLboolean customBoolean)
	{
		mCustomBoolean = customBoolean;
		logger.log(Logger::Level::LEVEL_TRACE, "BooleanSetting: " + mSettingName + " Default: " +
			toString(mDEFAULT_BOOLEAN) + " Custom: " + toString(mCustomBoolean));
	}


	void BooleanSetting::setCustomBoolean(std::string fileValue)
	{
		if (fileValue.compare(SETTING_TRUE) == 0)
		{
			setCustomBoolean(GL_TRUE);
		}
		else if (fileValue.compare(SETTING_FALSE) == 0)
		{
			setCustomBoolean(GL_FALSE);
		}
		else
		{
			logger.log(Logger::Level::LEVEL_WARN, "Could not read value: '" + fileValue + "'. Returning default value.");
			return setCustomBoolean(mDEFAULT_BOOLEAN);
		}
	}


	void BooleanSetting::operator=(GLboolean customBoolean)
	{
		setCustomBoolean(customBoolean);
	}


	GLboolean BooleanSetting::operator==(GLboolean anotherBoolean)
	{
		return (mCustomBoolean == anotherBoolean);
	}


	const GLboolean& BooleanSetting::getDefaultBoolean() const
	{
		return mDEFAULT_BOOLEAN;
	}
	
	
	const GLboolean& BooleanSetting::getCustomBoolean() const
	{
		return mCustomBoolean;
	}


	GLboolean BooleanSetting::isModified() const
	{
		return (mDEFAULT_BOOLEAN != mCustomBoolean);
	}


	std::string BooleanSetting::toString(GLboolean booleanValue)
	{
		return (booleanValue ? SETTING_TRUE : SETTING_FALSE);
	}


	std::string BooleanSetting::toFileString() const
	{
		return mSettingName + DELIMITER + toString(mCustomBoolean);
	}


	void BooleanSetting::resetCustomValue()
	{
		mCustomBoolean = mDEFAULT_BOOLEAN;
	}
}