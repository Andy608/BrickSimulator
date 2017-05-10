#include "BrickSimulator.h"

#include <string>
#include <iostream>

using namespace Bountive;

int main()
{
	BrickSimulator* simulator = nullptr;

	try
	{
		simulator = new BrickSimulator();
		simulator->start();
	}
	catch (std::string e)
	{
		delete simulator;
		std::cout << e << std::endl;
		return -1;
	}
	
	delete simulator;
	std::cin.get();
	return 0;
}