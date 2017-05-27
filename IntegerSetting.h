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
		static std::string toString(GLint integerValue);

		IntegerSetting(std::string settingName, const GLint DEFAULT_INTEGER);
		virtual ~IntegerSetting();

		virtual void setCustomInteger(GLint customInteger);
		void setCustomInteger(std::string fileValue);

		void operator=(GLint customInteger);
		GLboolean operator==(GLint anotherInteger);

		const GLint& getDefaultInteger() const;
		const GLint& getCustomInteger() const;

		virtual std::string toFileString() const;
		virtual GLboolean isModified() const;
		void resetCustomValue();

	protected:
		const GLint mDEFAULT_INTEGER;
		GLint mCustomInteger;

	private:
		static Logger logger;
	};
}

#endif