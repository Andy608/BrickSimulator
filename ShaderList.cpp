#include "ShaderList.h"
#include "ResourceBundleTracker.h"
#include "ResourceShaderProgram.h"
#include "GuiResourceBundle.h"
#include "Logger.h"

namespace Bountive
{
	ResourceShaderProgram** ShaderList::mGuiShaderProgram = &GuiResourceBundle::mGuiShaderProgram;
}