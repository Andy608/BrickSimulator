#include <iostream>
#include "BooleanSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger BooleanSetting::logger = Logger("BooleanSetting", Logger::Level::LEVEL_ALL);
	const std::wstring BooleanSetting::SETTING_TRUE = L"true";
	const std::wstring BooleanSetting::SETTING_FALSE = L"false";

	BooleanSetting::BooleanSetting(std::wstring settingName, const GLboolean DEFAULT_BOOLEAN) :
		SettingType(settingName), 
		mDEFAULT_BOOLEAN(DEFAULT_BOOLEAN), 
		mCustomBoolean(DEFAULT_BOOLEAN)
	{
		logger.log(Logger::Level::LEVEL_TRACE, L"Creating BooleanSetting: " + mSettingName);
	}


	BooleanSetting::~BooleanSetting() 
	{
		logger.log(Logger::Level::LEVEL_TRACE, L"Deleting BooleanSetting: " + mSettingName);
	}


	void BooleanSetting::setCustomBoolean(GLboolean customBoolean)
	{
		mCustomBoolean = customBoolean;
		logger.log(Logger::Level::LEVEL_TRACE, L"BooleanSetting: " + mSettingName + L" Default: " +
			toString(mDEFAULT_BOOLEAN) + L" Custom: " + toString(mCustomBoolean));
	}


	void BooleanSetting::setCustomBoolean(std::wstring fileValue)
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
			logger.log(Logger::Level::LEVEL_WARN, L"Could not read value: '" + fileValue + L"'. Returning default value.");
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


	std::wstring BooleanSetting::toString(GLboolean booleanValue)
	{
		return (booleanValue ? SETTING_TRUE : SETTING_FALSE);
	}


	std::wstring BooleanSetting::toFileString() const
	{
		return mSettingName + DELIMITER + toString(mCustomBoolean);
	}


	void BooleanSetting::resetCustomValue()
	{
		mCustomBoolean = mDEFAULT_BOOLEAN;
	}
}