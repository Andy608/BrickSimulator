#pragma once
#ifndef BOUNTIVE_SETTINGTYPE_H_
#define BOUNTIVE_SETTINGTYPE_H_

#include <glew.h>
#include <string>

namespace Bountive
{
	class SettingType
	{
	public:
		static const wchar_t DELIMITER;

		SettingType(std::wstring settingName);
		virtual ~SettingType() = 0;

		const std::wstring& getSettingName() const;

		virtual std::wstring toFileString() const = 0;

		virtual GLboolean isModified() const = 0;
		virtual void resetCustomValue() = 0;

	protected:
		std::wstring mSettingName;
	};
}

#endif