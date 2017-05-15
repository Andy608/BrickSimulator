#include "BooleanSetting.h"
#include <iostream>

namespace Bountive
{
	const std::wstring BooleanSetting::SETTING_TRUE = L"true";
	const std::wstring BooleanSetting::SETTING_FALSE = L"false";

	BooleanSetting::BooleanSetting(std::wstring settingName, const GLboolean DEFAULT_BOOLEAN) :
		SettingType(settingName), 
		mDEFAULT_BOOLEAN(DEFAULT_BOOLEAN), 
		mCustomBoolean(DEFAULT_BOOLEAN)
	{

	}


	BooleanSetting::~BooleanSetting() {}


	void BooleanSetting::setCustomBoolean(GLboolean customBoolean)
	{
		mCustomBoolean = customBoolean;
	}


	void BooleanSetting::setCustomBoolean(std::wstring fileValue)
	{
		if (fileValue.compare(SETTING_TRUE) == 0)
		{
			setCustomBoolean(true);
		}
		else if (fileValue.compare(SETTING_FALSE) == 0)
		{
			setCustomBoolean(false);
		}
		else
		{
			std::wcout << "Error reading value \'" << fileValue << "\'. Returning default value." << std::endl;
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


	const GLboolean& BooleanSetting::getDefaultBoolean()
	{
		return mDEFAULT_BOOLEAN;
	}
	
	
	const GLboolean& BooleanSetting::getCustomBoolean()
	{
		return mCustomBoolean;
	}


	GLboolean BooleanSetting::isModified() const
	{
		return (mDEFAULT_BOOLEAN != mCustomBoolean);
	}


	std::wstring BooleanSetting::toString() const
	{
		return mSettingName + DELIMITER + (mCustomBoolean ? SETTING_TRUE : SETTING_FALSE);
	}


	void BooleanSetting::resetCustomValue()
	{
		mCustomBoolean = mDEFAULT_BOOLEAN;
	}
}