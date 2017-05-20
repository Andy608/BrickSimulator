#pragma once
#ifndef BOUNTIVE_SINGLEKEYSETTING_H_
#define BOUNTIVE_SINGLEKEYSETTING_H_

#include "KeySetting.h"
#include "IntegerSetting.h"

namespace Bountive
{
	class Logger;

	class SingleKeySetting : public IntegerSetting, public KeySetting
	{
	public:
		SingleKeySetting(std::wstring settingName, const GLint DEFAULT_ASCII_VALUE);
		~SingleKeySetting();

		virtual const GLboolean& isPressed() const;

		void setNewPress(GLboolean isNewPress);
		const GLboolean& isNewPress() const;

	private:
		static Logger logger;

		GLboolean mNewPress;
	};
}

#endif