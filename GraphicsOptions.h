#pragma once
#ifndef GRAPHICSOPTIONS_H_
#define GRAPHICSOPTIONS_H_

#include <glew.h>
#include "FileSettingsHandler.h"

namespace Bountive
{
	class FileSettingsHandler;
	class Logger;

	enum class EnumProjection : GLuint
	{
		PERSPECTIVE,
		ORTHO
	};

	class GraphicsOptions
	{
	public:
		static GraphicsOptions* instance;

		static GraphicsOptions* init(const FileSettingsHandler& FILE_SETTINGS_HANDLER);

		~GraphicsOptions();

		void setProjectionType(const EnumProjection& PROJECTION_TYPE);
		EnumProjection getProjectionType() const;

		const IntegerSetting& getFieldOfView() const;
		const BooleanSetting& isVsyncEnabled() const;

	private:
		static Logger logger;

		const FileSettingsHandler& mFILE_SETTINGS_HANDLER;

		ClampedIntegerSetting& mFieldOfView;
		BooleanSetting& mVsyncEnabled;
		ClampedIntegerSetting& mProjectionType;

		GraphicsOptions(const FileSettingsHandler& FILE_SETTINGS_HANDLER);
	};
}

#endif