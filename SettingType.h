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
		static const GLchar DELIMITER;

		SettingType(std::string settingName);
		virtual ~SettingType() = 0;

		const std::string& getSettingName() const;

		virtual std::string toFileString() const = 0;

		virtual GLboolean isModified() const = 0;
		virtual void resetCustomValue() = 0;

	protected:
		std::string mSettingName;
	};
}

#endif