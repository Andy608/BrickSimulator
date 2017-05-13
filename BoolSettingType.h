#pragma once
#ifndef BOUNTIVE_BOOLSETTINGTYPE_H_
#define BOUNTIVE_BOOLSETTINGTYPE_H_

#include "SettingType.h"
#include <glew.h>

namespace Bountive
{
	class BooleanSettingType : public SettingType
	{
	public:
		static std::wstring toString(GLboolean booleanValue);

		BooleanSettingType(std::wstring settingName, const GLboolean DEFAULT_BOOLEAN);
		~BooleanSettingType();

		void setCustomBoolean(GLboolean customBoolean);
		void setCustomBoolean(std::wstring fileValue);

		void operator=(GLboolean customBoolean);
		GLboolean operator==(GLboolean anotherBoolean);

		const GLboolean& getDefaultBoolean();
		const GLboolean& getCustomBoolean();

		void resetBoolean();
		GLboolean isModified();

	private:
		static const std::wstring TRUE;
		static const std::wstring FALSE;

		const GLboolean mDEFAULT_BOOLEAN;
		GLboolean mCustomBoolean;
	};
}

#endif