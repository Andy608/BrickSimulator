#pragma once
#ifndef BOUNTIVE_INTEGERSETTING_H_
#define BOUNTIVE_INTEGERSETTING_H_

#include "SettingType.h"

namespace Bountive
{
	class Logger;

	class IntegerSetting : public SettingType
	{
	public:
		static std::wstring toString(GLint integerValue);

		IntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER);
		virtual ~IntegerSetting();

		virtual void setCustomInteger(GLint customInteger);
		void setCustomInteger(std::wstring fileValue);

		void operator=(GLint customInteger);
		GLboolean operator==(GLint anotherInteger);

		const GLint& getDefaultInteger() const;
		const GLint& getCustomInteger() const;

		virtual std::wstring toFileString() const;
		virtual GLboolean isModified() const;
		void resetCustomValue();

	protected:
		static Logger logger;
		const GLint mDEFAULT_INTEGER;
		GLint mCustomInteger;
	};
}

#endif