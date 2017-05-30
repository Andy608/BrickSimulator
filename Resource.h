#pragma once
#ifndef BOUNTIVE_RESOURCE_H_
#define BOUNTIVE_RESOURCE_H_

#include <string>
#include <glew.h>

namespace Bountive
{
	class Resource
	{
	public:
		Resource(const std::string RESOURCE_ID);
		virtual ~Resource();

		virtual GLboolean load() = 0;
		virtual void unload() = 0;
		
		const std::string getResourceId() const;
		const GLboolean& isLoaded() const;

	protected:
		const std::string mRESOURCE_ID;
		GLboolean mIsLoaded;
	};
}

#endif