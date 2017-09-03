#include "CursorPositionCallback.h"
#include "InputTracker.h"
#include "Logger.h"

namespace Bountive
{
	CursorPositionCallback* CursorPositionCallback::instance = nullptr;
	Logger CursorPositionCallback::logger = Logger("CursorPositionCallback", Logger::Level::LEVEL_ALL);

	CursorPositionCallback* CursorPositionCallback::init(InputTracker& INPUT_TRACKER)
	{
		if (instance == nullptr)
		{
			instance = new CursorPositionCallback(INPUT_TRACKER);
		}

		return instance;
	}


	CursorPositionCallback::CursorPositionCallback(InputTracker& INPUT_TRACKER) :
		mInputTracker(INPUT_TRACKER)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating CursorPositionCallback...");
	}


	CursorPositionCallback::~CursorPositionCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting CursorPositionCallback...");
	}


	void CursorPositionCallback::cursorPositionCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition)
	{
		instance->mInputTracker.updateCursorPosition(xPosition, yPosition);

		//logger.log(Logger::Level::LEVEL_TRACE, "Cursor Position: (" + std::to_string(xPosition) + ", " + std::to_string(yPosition) + ")");
	}
}