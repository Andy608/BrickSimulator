#include "ClampedIntegerSetting.h"
#include <iostream>

namespace Bountive
{
	ClampedIntegerSetting::ClampedIntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER, const GLint MIN_INTEGER, const GLint MAX_INTEGER) :
		IntegerSetting(settingName, DEFAULT_INTEGER),
		mMIN_INTEGER(MIN_INTEGER),
		mMAX_INTEGER(MAX_INTEGER)
	{

	}


	ClampedIntegerSetting::~ClampedIntegerSetting() {}


	void ClampedIntegerSetting::setCustomInteger(GLint customInteger)
	{
		mCustomInteger = clamp(customInteger);
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
		}
		else if (customInteger < mMIN_INTEGER)
		{
			customInteger = mMIN_INTEGER;
		}

		return customInteger;
	}
}