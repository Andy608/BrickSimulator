#pragma once
#ifndef BOUNTIVE_INTEGERSETTING_H_
#define BOUNTIVE_INTEGERSETTING_H_

#include "SettingType.h"

namespace Bountive
{
	class IntegerSetting : public SettingType
	{
	public:
		IntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER);
		virtual ~IntegerSetting();

		virtual void setCustomInteger(GLint customInteger);
		void setCustomInteger(std::wstring fileValue);

		void operator=(GLint customInteger);
		GLboolean operator==(GLint anotherInteger);

		const GLint& getDefaultInteger() const;
		const GLint& getCustomInteger() const;

		virtual std::wstring toString() const;
		virtual GLboolean isModified() const;
		void resetCustomValue();

	protected:
		const GLint mDEFAULT_INTEGER;
		GLint mCustomInteger;
	};
}

#endif