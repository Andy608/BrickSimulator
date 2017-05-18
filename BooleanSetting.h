#pragma once
#ifndef BOUNTIVE_BOOLEANSETTING_H_
#define BOUNTIVE_BOOLEANSETTING_H_

#include "SettingType.h"

namespace Bountive
{
	class Logger;

	class BooleanSetting : public SettingType
	{
	public:
		static std::wstring toString(GLboolean booleanValue);

		BooleanSetting(std::wstring settingName, const GLboolean DEFAULT_BOOLEAN);
		virtual ~BooleanSetting();

		void setCustomBoolean(GLboolean customBoolean);
		void setCustomBoolean(std::wstring fileValue);

		void operator=(GLboolean customBoolean);
		GLboolean operator==(GLboolean anotherBoolean);

		const GLboolean& getDefaultBoolean() const;
		const GLboolean& getCustomBoolean() const;

		virtual std::wstring toFileString() const;
		virtual GLboolean isModified() const;
		virtual void resetCustomValue();

	private:
		static Logger logger;
		static const std::wstring SETTING_TRUE;
		static const std::wstring SETTING_FALSE;

		const GLboolean mDEFAULT_BOOLEAN;
		GLboolean mCustomBoolean;
	};
}

#endif