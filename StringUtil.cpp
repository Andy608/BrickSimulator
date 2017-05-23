#include "StringUtil.h"

namespace Bountive
{
	std::string StringUtil::wtos(const std::wstring& wstr)
	{
		return std::string(wstr.begin(), wstr.end());
	}


	std::wstring StringUtil::stow(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}
}