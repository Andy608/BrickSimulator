#pragma once
#ifndef BOUNTIVE_RESOURCEBUNDLE_H_
#define BOUNTIVE_RESOURCEBUNDLE_H_

#include <vector>
#include "Resource.h"

namespace Bountive
{
	class Logger;

	class ResourceBundle
	{
	public:
		enum class BundleID : const GLint
		{
			GUI = 0
		};

		const BundleID mPACKAGE_ID;

		ResourceBundle(const BundleID& PACKAGE_ID);
		virtual ~ResourceBundle();

		virtual void loadResourceBundle();
		virtual void unloadResourceBundle();

		Resource* findResource(std::string RESOURCE_ID) const;
		const GLboolean& isLoaded() const;


	protected:
		static GLint FULLY_LOADED;

		std::vector<Resource*>* mResourceList;
		GLfloat mPercentLoaded;
		GLboolean mIsLoaded;

	private:
		static Logger logger;
	};
}

#endif