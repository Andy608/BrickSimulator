#pragma once
#ifndef BOUNTIVE_FORMATTEDLAYOUT_H_
#define BOUNTIVE_FORMATTEDLAYOUT_H_

#include <log4cxx\patternlayout.h>

namespace Bountive
{
	class FormattedLayout : public log4cxx::PatternLayout
	{
	public:
		FormattedLayout();
		~FormattedLayout();

	private:

	};
}

#endif