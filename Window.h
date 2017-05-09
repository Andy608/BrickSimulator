#pragma once
#ifndef BRICKSIMULATOR_WINDOW_H_
#define BRICKSIMULATOR_WINDOW_H_

#include <glfw\glfw3.h>
#include <glm\glm.hpp>

namespace BrickSimulator
{
	class Window
	{
	public:
		
		/** Constructors */
		Window();
		
		/** Destructor */
		~Window();




	private:
		GLFWwindow* windowHandle;
	};
}


#endif