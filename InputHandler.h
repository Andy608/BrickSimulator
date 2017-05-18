#pragma once
#ifndef BOUNTIVE_INPUTHANDLER_H_
#define BOUNTIVE_INPUTHANDLER_H_

namespace Bountive
{
	class Logger;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void update();

	private:
		static Logger logger;
	};
}

#endif