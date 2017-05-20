#pragma once
#ifndef BOUNTIVE_WINDOW_H_
#define BOUNTIVE_WINDOW_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include <glm\vec2.hpp>

namespace Bountive
{
	class CallbackManager;
	class GameSettingsHandler;
	class SceneManager;
	class Logger;

	class Window
	{
	public:
		static GLint DECORATION_HEIGHT;
		//static Window* instance;

		//static Window* init();

		const GLFWvidmode* mVIDEO_MODE;
		const GLint mMINIMUM_SIZE_X;
		const GLint mMINIMUM_SIZE_Y;
		const GLint mMAXIMUM_SIZE_X;
		const GLint mMAXIMUM_SIZE_Y;

		Window();
		~Window();

		void buildWindow(GameSettingsHandler& gameSettingsHandler);
		void update(const GLdouble& DELTA_TIME);
		void render(const GLdouble& DELTA_TIME);

		GLFWwindow* getWindowHandle() const;
		glm::vec2 getMinimumWindowPosition() const;
		glm::vec2 getMaximumWindowPosition() const;


	private:
		static Logger logger;
		static const GLFWvidmode* initGLFW();

		GLFWwindow* mWindowHandle;
		CallbackManager* mCallbackManager;
		SceneManager* mSceneManager;
	};
}

#endif