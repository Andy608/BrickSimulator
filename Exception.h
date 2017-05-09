#pragma once
#ifndef BRICKSIMULATOR_EXCEPTION_H_
#define BRICKSIMULATOR_EXCEPTION_H_

#include <string>

namespace BrickSimulator
{
	class Exception
	{
	public:
		Exception();
		~Exception();

		const std::string& getErrorMessage() const;

	private:
		std::string errorMessage;
	};
}

#endif