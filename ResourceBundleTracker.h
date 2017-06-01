#pragma once
#ifndef BOUNTIVE_RESOURCEBUNDLETRACKER_H_
#define BOUNTIVE_RESOURCEBUNDLETRACKER_H_

#include <glew.h>
#include <vector>
#include "ResourceBundle.h"

namespace Bountive
{
	class Logger;

	class ResourceBundleTracker
	{
	public:
		ResourceBundleTracker();
		~ResourceBundleTracker();

		void loadBundle(const ResourceBundle::BundleID& PACKAGE_ID);
		void unloadBundle(const ResourceBundle::BundleID& PACKAGE_ID);

		ResourceBundle* getBundle(const ResourceBundle::BundleID& PACKAGE_ID) const;

	private:
		static Logger logger;

		std::vector<ResourceBundle*>* mBundleList;
	};
}

#endif