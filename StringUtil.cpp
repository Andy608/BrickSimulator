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


	void StringUtil::splitString(const std::string& str, const char DELIMITER, std::vector<std::string> &result)
	{
		GLuint begin = 0;

		for (GLuint i = 0; i < str.length(); ++i)
		{
			if (str.at(i) == DELIMITER)
			{
				std::string sub = str.substr(begin, i - begin);
				result.push_back(sub);
				begin = i + 1;
			}
			else if (i == str.length() - 1)
			{
				std::string sub = str.substr(begin);
				result.push_back(sub);
				return;
			}
		}
	}
}