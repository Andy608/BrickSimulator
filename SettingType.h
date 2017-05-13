#pragma once
#ifndef BOUNTIVE_SETTINGTYPE_H_
#define BOUNTIVE_SETTINGTYPE_H_

#include <string>

namespace Bountive
{
	class SettingType
	{
	public:
		SettingType(std::wstring settingName);
		virtual ~SettingType() = 0;

		const std::wstring& getSettingName();

	private:
		std::wstring mSettingName;
	};
}

#endif