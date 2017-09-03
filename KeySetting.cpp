#include "KeySetting.h"

namespace Bountive
{
	KeySetting::KeySetting() :
		mPressed(GL_FALSE)
	{

	}

	KeySetting::~KeySetting()
	{

	}


	void KeySetting::setPressed(GLboolean isPressed)
	{
		mPressed = isPressed;
	}
}