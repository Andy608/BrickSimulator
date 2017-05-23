#pragma once
#ifndef BOUNTIVE_STRINGUTIL_H_
#define BOUNTIVE_STRINGUTIL_H_

#include <string>

namespace Bountive
{
	class StringUtil
	{
	public:
		static std::string StringUtil::wtos(const std::wstring& wstr);
		static std::wstring StringUtil::stow(const std::string& str);

	private:
		StringUtil();
	};
}

#endif