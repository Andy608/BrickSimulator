#include <string>
#include <log4cxx\helpers\exception.h>
#include "BrickSimulator.h"
#include "Logger.h"

using namespace Bountive;

int main()
{
	Logger logger = Logger("main", Logger::Level::LEVEL_ALL);
	GLint exitResult = EXIT_SUCCESS;
	BrickSimulator* simulator = nullptr;

	try
	{
		simulator = BrickSimulator::init();
		simulator->start();
	}
	catch (std::wstring e)
	{
		logger.log(Logger::Level::LEVEL_ERROR, e);
		exitResult = EXIT_FAILURE;
	}
	catch (log4cxx::helpers::Exception& e)
	{
		//LOGGER.log(e.getLevel(), e.what());
		logger.log(Logger::Level::LEVEL_ERROR, e.what());
		exitResult = EXIT_FAILURE;
	}
	
	delete simulator;
	return exitResult;
}