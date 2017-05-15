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


	SettingType::operator std::wstring() const
	{
		return toString();
	}


	std::wstring operator+(std::wstring another, SettingType& setting)
	{
		return another + setting.toString();
	}
}