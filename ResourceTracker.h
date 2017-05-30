#pragma once
#ifndef BOUNTIVE_RESOURCETRACKER_H_
#define BOUNTIVE_RESOURCETRACKER_H_

#include "StartupResourceLoader.h"

namespace Bountive
{
	class Logger;

	class ResourceTracker
	{
	public:
		ResourceTracker();
		~ResourceTracker();

		void initResourcePackage(const ResourceLoader::ResourcePackageId& PACKAGE_ID);
		void loadResourcePackage(const ResourceLoader::ResourcePackageId& PACKAGE_ID);

	private:
		static Logger logger;
		//Make this a list of loader packages
		StartupResourceLoader* mStartupResourceManager;
		GLint mTotalPercentLoaded;
	};
}

#endif