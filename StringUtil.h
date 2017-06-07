#pragma once
#ifndef BOUNTIVE_STRINGUTIL_H_
#define BOUNTIVE_STRINGUTIL_H_

#include <glew.h>
#include <string>
#include <vector>

namespace Bountive
{
	class StringUtil
	{
	public:
		static std::string StringUtil::wtos(const std::wstring& wstr);
		static std::wstring StringUtil::stow(const std::string& str);
		static void StringUtil::splitString(const std::string& str, const char DELIMITER, std::vector<std::string> &result);

	private:
		StringUtil();
	};
}

#endif