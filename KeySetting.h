#pragma once
#ifndef BOUNTIVE_KEYSETTING_H_
#define BOUNTIVE_KEYSETTING_H_

#include "SettingType.h"

namespace Bountive
{
	class KeySetting
	{
	public:
		virtual ~KeySetting();

		virtual const GLboolean& isPressed() const = 0;
		void setPressed(GLboolean isPressed);

	protected:
		GLboolean mPressed;
	};
}

#endif