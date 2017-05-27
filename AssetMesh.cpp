#include "AssetMesh.h"
#include "Logger.h"

namespace Bountive
{
	Logger AssetMesh::logger = Logger("AssetMesh", Logger::Level::LEVEL_ALL);

	AssetMesh::AssetMesh(const std::wstring ASSET_ID) :
		Asset(ASSET_ID),
		mVertexArray(new VertexArrayWrapper()),
		mVertexBufferList(new std::vector<VertexBufferWrapper*>()),
		mElementBufferData(nullptr)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating AssetMesh: \'" + mASSET_ID + L"\'");
	}


	AssetMesh::~AssetMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting AssetMesh: \'" + mASSET_ID + L"\'");
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


	void AssetMesh::addVertexBuffer(VertexBufferWrapper* wrapper)
	{
		mVertexBufferList->push_back(wrapper);
	}


	void AssetMesh::setElementBuffer(ElementBufferWrapper* wrapper)
	{
		mElementBufferData = wrapper;
	}


	VertexArrayWrapper* const AssetMesh::getVertexArray() const
	{
		return mVertexArray;
	}


	VertexBufferWrapper* const  AssetMesh::getVertexBufferList(GLint bufferIndex) const
	{
		return mVertexBufferList->at(bufferIndex);
	}


	ElementBufferWrapper* const  AssetMesh::getElementBufferData() const
	{
		return mElementBufferData;
	}


	void AssetMesh::addBufferData(VertexBufferWrapper* bufferData)
	{
		mVertexBufferList->push_back(bufferData);
	}


	void AssetMesh::prepareMesh()
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


	void AssetMesh::clearBufferData()
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