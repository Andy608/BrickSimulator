#pragma once
#ifndef BOUNTIVE_WINDOW_H_
#define BOUNTIVE_WINDOW_H_

#include "CallbackManager.h"

namespace Bountive
{
	class Window
	{
	public:
		Window();
		~Window();

		GLFWwindow* getWindowHandle() const;

	private:
		const GLFWvidmode* mVIDEO_MODE;
		GLFWwindow* mWindowHandle;
		CallbackManager* mCallbackManager;
	};
}

#endif