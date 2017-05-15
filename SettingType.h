#pragma once
#ifndef BOUNTIVE_SETTINGTYPE_H_
#define BOUNTIVE_SETTINGTYPE_H_

#include <string>
#include <glew.h>

namespace Bountive
{
	class SettingType
	{
	public:
		static const wchar_t DELIMITER;

		SettingType(std::wstring settingName);
		virtual ~SettingType() = 0;

		const std::wstring& getSettingName() const;

		virtual operator std::wstring() const;
		virtual std::wstring toString() const = 0;
		friend std::wstring operator+(std::wstring another, SettingType& setting);

		virtual GLboolean isModified()const = 0;
		virtual void resetCustomValue() = 0;

	protected:
		std::wstring mSettingName;
	};
}

#endif