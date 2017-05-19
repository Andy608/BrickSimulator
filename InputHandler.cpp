#include "InputHandler.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger InputHandler::logger = Logger("InputHandler", Logger::Level::LEVEL_ALL);

	InputHandler::InputHandler()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating InputHandler...");
	}


	InputHandler::~InputHandler()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting InputHandler...");
	}


	void InputHandler::update()
	{
		//Depending on screen do something else.

		if (KeyboardCallback::isKeyEscapePressed())
		{
			glfwSetWindowShouldClose(Window::instance->getWindowHandle(), GL_TRUE);
		}
	}
}