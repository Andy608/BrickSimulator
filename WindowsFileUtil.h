#pragma once
#ifndef BOUNTIVE_WINDOWSFILEUTIL_H_
#define BOUNTIVE_WINDOWSFILEUTIL_H_

#include "FileUtil.h"

namespace Bountive
{
	class WindowsFileUtil : public FileUtil
	{
	public:
		WindowsFileUtil();
		virtual ~WindowsFileUtil();
	};
}

#endif