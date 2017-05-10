#include "CallbackManager.h"
#include  <iostream>

namespace Bountive
{
	CallbackManager::CallbackManager(GLFWwindow* windowHandle) :
		mWindowHandle(windowHandle), 
		mKeyboardCallback(KeyboardCallback::init())
	{
		glfwSetKeyCallback(mWindowHandle, mKeyboardCallback->keyCallback);
	}


	CallbackManager::~CallbackManager()
	{
		std::cout << "Deleting Window Callbacks." << std::endl;
		delete mKeyboardCallback;
	}
}