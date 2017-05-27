#include "SettingType.h"

namespace Bountive
{
	const GLchar SettingType::DELIMITER = '=';

	SettingType::SettingType(std::string settingName) :
		mSettingName(settingName)
	{

	}


	SettingType::~SettingType() {}


	const std::string& SettingType::getSettingName() const
	{
		return mSettingName;
	}
}