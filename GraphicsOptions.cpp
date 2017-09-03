#include "GraphicsOptions.h"
#include "Logger.h"
#include "FileSettingsHandler.h"

namespace Bountive
{
	GraphicsOptions* GraphicsOptions::instance = nullptr;
	Logger GraphicsOptions::logger = Logger("GraphicsOptions", Logger::Level::LEVEL_ALL);

	GraphicsOptions* GraphicsOptions::init(const FileSettingsHandler& FILE_SETTINGS_HANDLER)
	{
		if (instance == nullptr)
		{
			instance = new GraphicsOptions(FILE_SETTINGS_HANDLER);
		}

		return instance;
	}


	GraphicsOptions::GraphicsOptions(const FileSettingsHandler& FILE_SETTINGS_HANDLER) :
		mFILE_SETTINGS_HANDLER(FILE_SETTINGS_HANDLER),
		mFieldOfView(*FILE_SETTINGS_HANDLER.getFieldOfView()),
		mVsyncEnabled(*FILE_SETTINGS_HANDLER.isVsyncEnabled()),
		mProjectionType(*FILE_SETTINGS_HANDLER.getProjectionID())
	{

	}


	GraphicsOptions::~GraphicsOptions()
	{

	}


	void GraphicsOptions::setProjectionType(const EnumProjection& PROJECTION_TYPE)
	{
		mProjectionType.setCustomInteger(static_cast<GLint>(PROJECTION_TYPE));
	}


	EnumProjection GraphicsOptions::getProjectionType() const
	{
		switch (mProjectionType.getCustomInteger())
		{
		case static_cast<GLint>(EnumProjection::PERSPECTIVE) :
			return EnumProjection::PERSPECTIVE;
		default :
			return EnumProjection::ORTHO;
		}
	}


	const IntegerSetting& GraphicsOptions::getFieldOfView() const
	{
		return mFieldOfView;
	}


	const BooleanSetting& GraphicsOptions::isVsyncEnabled() const
	{
		return mVsyncEnabled;
	}
}
