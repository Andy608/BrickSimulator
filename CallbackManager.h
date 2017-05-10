#pragma once
#ifndef BOUNTIVE_CALLBACKMANAGER_H_
#define BOUNTIVE_CALLBACKMANAGER_H_

#include "KeyboardCallback.h"

namespace Bountive
{
	class CallbackManager
	{
	public:
		CallbackManager(GLFWwindow* windowHandle);
		~CallbackManager();


	private:
		GLFWwindow* mWindowHandle;
		KeyboardCallback* mKeyboardCallback;
	};
}

#endif