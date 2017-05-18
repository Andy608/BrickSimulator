#include "SettingType.h"

namespace Bountive
{
	const wchar_t SettingType::DELIMITER = L'=';

	SettingType::SettingType(std::wstring settingName) :
		mSettingName(settingName)
	{

	}


	SettingType::~SettingType() {}


	const std::wstring& SettingType::getSettingName() const
	{
		return mSettingName;
	}
}