#pragma once
#ifndef BOUNTIVE_SHADERLIST_H_
#define BOUNTIVE_SHADERLIST_H_

namespace Bountive
{
	class ResourceBundleTracker;
	class ResourceShaderProgram;
	class Logger;

	class ShaderList
	{
	public:
		static ResourceShaderProgram** mGuiShaderProgram;

	private:
		ShaderList();
	};
}

#endif