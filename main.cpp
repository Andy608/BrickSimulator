#include <iostream>
#include <string>
#include "BrickSimulator.h"

using namespace Bountive;

int main()
{
	GLint exitResult = EXIT_SUCCESS;
	BrickSimulator* simulator = nullptr;

	try
	{
		simulator = BrickSimulator::init();
		simulator->start();
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
		exitResult = EXIT_FAILURE;
	}
	
	delete simulator;
	std::cin.get();
	return exitResult;
}