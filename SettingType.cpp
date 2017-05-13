#include "SettingType.h"

namespace Bountive
{
	SettingType::SettingType(std::wstring settingName) :
		mSettingName(settingName)
	{

	}


	SettingType::~SettingType() {}


	const std::wstring& SettingType::getSettingName()
	{
		return mSettingName;
	}
}