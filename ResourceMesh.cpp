#include "ResourceMesh.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceMeshOld::logger = Logger("ResourceMesh", Logger::Level::LEVEL_ALL);

	ResourceMeshOld::ResourceMeshOld(const std::string RESOURCE_ID) :
		Resource(RESOURCE_ID),
		mVertexArray(new VertexArrayWrapper()),
		mVertexBufferList(new std::vector<VertexBufferWrapper*>()),
		mElementBufferData(nullptr)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetMesh: \'" + mRESOURCE_ID + "\'");
	}


	ResourceMeshOld::~ResourceMeshOld()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetMesh: \'" + mRESOURCE_ID + "\'");
		unload();
	}


	void ResourceMeshOld::load()
	{
		//load information from file
	}


	void ResourceMeshOld::unload()
	{
		clearBufferData();

		if (mVertexBufferList != nullptr)
		{
			delete mVertexBufferList;
		}

		if (mElementBufferData != nullptr)
		{
			delete mElementBufferData;
		}

		if (mVertexArray != nullptr)
		{
			delete mVertexArray;
		}
	}


	void ResourceMeshOld::addVertexBuffer(VertexBufferWrapper* wrapper)
	{
		mVertexBufferList->push_back(wrapper);
	}


	void ResourceMeshOld::setElementBuffer(ElementBufferWrapper* wrapper)
	{
		mElementBufferData = wrapper;
	}


	VertexArrayWrapper* const ResourceMeshOld::getVertexArray() const
	{
		return mVertexArray;
	}


	VertexBufferWrapper* const ResourceMeshOld::getVertexBufferList(GLint bufferIndex) const
	{
		return mVertexBufferList->at(bufferIndex);
	}


	ElementBufferWrapper* const  ResourceMeshOld::getElementBufferData() const
	{
		return mElementBufferData;
	}


	void ResourceMeshOld::addBufferData(VertexBufferWrapper* bufferData)
	{
		mVertexBufferList->push_back(bufferData);
	}


	void ResourceMeshOld::prepareMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Binding VAO: " + std::to_string(mVertexArray->getId()));
		mVertexArray->bind();

		logger.log(Logger::Level::LEVEL_DEBUG, "Binding EBO: " + std::to_string(mElementBufferData->getId()));
		mElementBufferData->bind();

		logger.log(Logger::Level::LEVEL_DEBUG, "Binding VBO: " + std::to_string(mVertexBufferList->at(0)->getId()));
		
		for (GLuint i = 0; i < mVertexBufferList->size(); ++i)
		{
			mVertexBufferList->at(i)->bind();
			mVertexArray->bindVBOToVAO(i, mVertexBufferList->at(i));
			mVertexBufferList->at(i)->unbind();
		}

		logger.log(Logger::Level::LEVEL_DEBUG, "Unbinding VAO: " + std::to_string(mVertexArray->getId()));
		mVertexArray->unbind();
	}


	void ResourceMeshOld::clearBufferData()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Clearing bufferdata! Buffers in list: " + std::to_string(mVertexBufferList->size()));

		for (GLuint i = 0; i < mVertexBufferList->size(); ++i)
		{
			if (mVertexBufferList->at(i) != nullptr)
			{
				delete mVertexBufferList->at(i);
			}
		}

		mVertexBufferList->clear();
	}
}