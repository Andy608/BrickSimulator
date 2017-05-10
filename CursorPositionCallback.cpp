#include "CursorPositionCallback.h"
#include <iostream>

namespace Bountive
{
	CursorPositionCallback* CursorPositionCallback::instance = nullptr;

	CursorPositionCallback* CursorPositionCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new CursorPositionCallback();
		}

		return instance;
	}


	CursorPositionCallback::CursorPositionCallback() {}


	CursorPositionCallback::~CursorPositionCallback()
	{
		std::cout << "Deleting CursorPositionCallback." << std::endl;
	}


	void CursorPositionCallback::cursorPositionCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition)
	{
		//TODO: Save position in options
		std::cout << "Cursor Position: (" << xPosition << ", " << yPosition << ")" << std::endl;
	}
}