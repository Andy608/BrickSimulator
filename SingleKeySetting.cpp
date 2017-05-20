#include "SingleKeySetting.h"
#include "IntegerSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger SingleKeySetting::logger = Logger("SingleKeySetting", Logger::Level::LEVEL_ALL);

	SingleKeySetting::SingleKeySetting(std::wstring settingName, const GLint DEFAULT_ASCII_VALUE) :
		IntegerSetting(settingName, DEFAULT_ASCII_VALUE),
		mNewPress(GL_TRUE)
	{
		logger.log(Logger::Level::LEVEL_TRACE, L"Creating SingleKeySetting" + mSettingName);
	}


	SingleKeySetting::~SingleKeySetting()
	{

	}


	const GLboolean& SingleKeySetting::isPressed() const
	{
		return mPressed;
	}


	void SingleKeySetting::setNewPress(GLboolean isNewPress)
	{
		mNewPress = isNewPress;
	}


	const GLboolean& SingleKeySetting::isNewPress() const
	{
		return mNewPress;
	}
}