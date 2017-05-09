#include "Window.h"

namespace BrickSimulator
{

	Window::Window()
	{
		//Create a window in the center of the screen 2/3 the size of the monitor
	}


	Window::~Window()
	{
		glfwTerminate();
	}



}