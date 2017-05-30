#include "Resource.h"

namespace Bountive
{
	Resource::Resource(const std::string RESOURCE_ID) :
		mRESOURCE_ID(RESOURCE_ID),
		mIsLoaded(GL_FALSE)
	{

	}


	Resource::~Resource()
	{

	}


	const std::string Resource::getResourceId() const
	{
		return mRESOURCE_ID;
	}


	const GLboolean& Resource::isLoaded() const
	{
		return mIsLoaded;
	}
}