#include <stdexcept> 
#include <iostream>
#include "IntegerSetting.h"

namespace Bountive
{
	IntegerSetting::IntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER) :
		SettingType(settingName), 
		mDEFAULT_INTEGER(DEFAULT_INTEGER), 
		mCustomInteger(DEFAULT_INTEGER)
	{

	}


	IntegerSetting::~IntegerSetting() {}


	void IntegerSetting::setCustomInteger(GLint customInteger)
	{
		mCustomInteger = customInteger;
	}


	void IntegerSetting::setCustomInteger(std::wstring fileValue)
	{
		try
		{
			setCustomInteger(std::stoi(fileValue));
		}
		catch (const std::invalid_argument e)
		{
			std::wcout << "Could not convert \'" << fileValue << "\'. to integer." << std::endl;
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


	std::wstring IntegerSetting::toString() const
	{
		return mSettingName + DELIMITER + std::to_wstring(mCustomInteger);
	}


	void IntegerSetting::resetCustomValue()
	{
		mCustomInteger = mDEFAULT_INTEGER;
	}
}