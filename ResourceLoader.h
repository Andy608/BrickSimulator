#pragma once
#ifndef BOUNTIVE_RESOURCELOADER_H_
#define BOUNTIVE_RESOURCELOADER_H_

#include <vector>
#include "Resource.h"

namespace Bountive
{
	class Logger;

	class ResourceLoader
	{
	public:
		enum class ResourcePackageId : GLint
		{
			START_UP
		};

		ResourceLoader(const ResourcePackageId& PACKAGE_ID);
		virtual ~ResourceLoader();

		virtual void initResources() = 0;
		
		void addResource(Resource* asset);

		void loadResources();
		void unloadResources();

		Resource* findResource(std::string resourceId);

		void clearResourceList();

	private:
		static Logger logger;
		const ResourcePackageId& mRESOURCE_PACKAGE_ID;
		std::vector<Resource*>* mResourceList;
		GLfloat mPercentLoaded;
	};
}

#endif