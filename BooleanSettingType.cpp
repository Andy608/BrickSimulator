#include "BoolSettingType.h"
#include <iostream>

namespace Bountive
{
	const std::wstring BooleanSettingType::TRUE = L"true";
	const std::wstring BooleanSettingType::FALSE = L"false";

	std::wstring BooleanSettingType::toString(GLboolean booleanValue)
	{
		return (booleanValue ? TRUE : FALSE);
	}


	BooleanSettingType::BooleanSettingType(std::wstring settingName, const GLboolean DEFAULT_BOOLEAN) :
		SettingType(settingName), mDEFAULT_BOOLEAN(DEFAULT_BOOLEAN), mCustomBoolean(DEFAULT_BOOLEAN)
	{

	}


	BooleanSettingType::~BooleanSettingType() {}


	void BooleanSettingType::setCustomBoolean(GLboolean customBoolean)
	{
		mCustomBoolean = customBoolean;
	}


	void BooleanSettingType::setCustomBoolean(std::wstring fileValue)
	{
		if (fileValue.compare(TRUE) == 0)
		{
			setCustomBoolean(true);
		}
		else if (fileValue.compare(FALSE) == 0)
		{
			setCustomBoolean(false);
		}
		else
		{
			std::wcout << "Error reading value \'" << fileValue << "\'. Returning default value." << std::endl;
			return setCustomBoolean(mDEFAULT_BOOLEAN);
		}
	}


	void BooleanSettingType::operator=(GLboolean customBoolean)
	{
		setCustomBoolean(customBoolean);
	}


	GLboolean BooleanSettingType::operator==(GLboolean anotherBoolean)
	{
		return (mCustomBoolean == anotherBoolean);
	}


	const GLboolean& BooleanSettingType::getDefaultBoolean()
	{
		return mDEFAULT_BOOLEAN;
	}
	
	
	const GLboolean& BooleanSettingType::getCustomBoolean()
	{
		return mCustomBoolean;
	}

	
	void BooleanSettingType::resetBoolean()
	{
		mCustomBoolean = mDEFAULT_BOOLEAN;
	}


	GLboolean BooleanSettingType::isModified()
	{
		return (mDEFAULT_BOOLEAN != mCustomBoolean);
	}
}