#include <iostream>
#include "InputHandler.h"
#include "KeyboardCallback.h"
#include "Window.h"

namespace Bountive
{
	InputHandler::InputHandler()
	{

	}


	InputHandler::~InputHandler()
	{
		std::wcout << "Deleting InputHandler." << std::endl;
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