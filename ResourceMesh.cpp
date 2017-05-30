#include "ResourceMesh.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceMesh::logger = Logger("ResourceMesh", Logger::Level::LEVEL_ALL);

	ResourceMesh::ResourceMesh(const std::string RESOURCE_ID) :
		Resource(RESOURCE_ID),
		mVertexArray(new VertexArrayWrapper()),
		mVertexBufferList(new std::vector<VertexBufferWrapper*>()),
		mElementBufferData(nullptr)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetMesh: \'" + mRESOURCE_ID + "\'");
	}


	ResourceMesh::~ResourceMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetMesh: \'" + mRESOURCE_ID + "\'");
		unload();
	}


	GLboolean ResourceMesh::load()
	{
		//load information from file
		mIsLoaded = GL_TRUE;
		return mIsLoaded;
	}


	void ResourceMesh::unload()
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


	void ResourceMesh::addVertexBuffer(VertexBufferWrapper* wrapper)
	{
		mVertexBufferList->push_back(wrapper);
	}


	void ResourceMesh::setElementBuffer(ElementBufferWrapper* wrapper)
	{
		mElementBufferData = wrapper;
	}


	VertexArrayWrapper* const ResourceMesh::getVertexArray() const
	{
		return mVertexArray;
	}


	VertexBufferWrapper* const  ResourceMesh::getVertexBufferList(GLint bufferIndex) const
	{
		return mVertexBufferList->at(bufferIndex);
	}


	ElementBufferWrapper* const  ResourceMesh::getElementBufferData() const
	{
		return mElementBufferData;
	}


	void ResourceMesh::addBufferData(VertexBufferWrapper* bufferData)
	{
		mVertexBufferList->push_back(bufferData);
	}


	void ResourceMesh::prepareMesh()
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


	void ResourceMesh::clearBufferData()
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