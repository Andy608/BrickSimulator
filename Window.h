#pragma once
#ifndef BOUNTIVE_WINDOW_H_
#define BOUNTIVE_WINDOW_H_

#include "CallbackManager.h"
#include "GameSettingsHandler.h"

namespace Bountive
{
	class Window
	{
	public:
		static Window* instance;
		static Window* init();

		const GLFWvidmode* mVIDEO_MODE;
		const GLint mMINIMUM_SIZE_X;
		const GLint mMINIMUM_SIZE_Y;
		const GLint mMAXIMUM_SIZE_X;
		const GLint mMAXIMUM_SIZE_Y;

		~Window();

		void buildWindow();
		GLFWwindow* getWindowHandle() const;
		glm::vec2 getMinimumWindowPosition() const;
		glm::vec2 getMaximumWindowPosition() const;

	private:
		static const GLFWvidmode* initGLFW();

		GLFWwindow* mWindowHandle;
		CallbackManager* mCallbackManager;

		Window();
	};
}

#endif