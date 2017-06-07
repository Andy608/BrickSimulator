#include "ResourceMesh.h"
#include "FileReader.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	const char ResourceMesh::SPACE_DELIMITER = ' ';
	const char ResourceMesh::SLASH_DELIMITER = '/';

	FileReader ResourceMesh::fileReader = FileReader();
	Logger ResourceMesh::logger = Logger("ResourceMesh", Logger::Level::LEVEL_ALL);

	ResourceMesh::ResourceMesh(const std::string RESOURCE_ID, const FileLocation& MESH_FILE_LOCATION) :
		Resource(RESOURCE_ID),
		mMESH_FILE_LOCATION(MESH_FILE_LOCATION),
		mVertexArray(nullptr),
		mVertexBufferList(new std::vector<VertexBufferWrapper*>()),
		mElementBufferData(nullptr)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetMesh: \'" + mRESOURCE_ID + "\'");
	}


	ResourceMesh::~ResourceMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetMesh: \'" + mRESOURCE_ID + "\'");
		
		if (mIsLoaded)
		{
			unload();
		}

		delete mVertexBufferList;
		delete mVertexArray;
	}


	void ResourceMesh::load()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Mesh already loaded: " + mMESH_FILE_LOCATION.getFullPath());
			return;
		}

		logger.log(Logger::Level::LEVEL_DEBUG, L"Loading Mesh from file location: " + mMESH_FILE_LOCATION.getFullPath());

		std::vector<std::string> modelFile = fileReader.getLinesInFile(mMESH_FILE_LOCATION);

		//std::string modelName = modelFile->at(2).substr(2);

		std::vector<GLfloat> unorderedPositions;
		std::vector<GLfloat> unorderedTextureCoords;
		std::vector<GLfloat> unorderedNormals;
		GLuint faceLine = 0;

		logger.log(Logger::Level::LEVEL_DEBUG, "Lines: " + std::to_string(modelFile.size()));

		for (GLuint i = 3; i < modelFile.size(); ++i)
		{
			std::string line = modelFile.at(i);

			if (line.substr(0, 2).compare("v ") == 0)
			{
				addFloatsFromString(line, unorderedPositions, 2, 3, SPACE_DELIMITER);
				continue;
			}
			else if (line.substr(0, 2).compare("vt") == 0)
			{
				addFloatsFromString(line, unorderedTextureCoords, 3, 2, SPACE_DELIMITER);
				continue;
			}
			else if (line.substr(0, 2).compare("vn") == 0)
			{
				addFloatsFromString(line, unorderedNormals, 3, 3, SPACE_DELIMITER);
				continue;
			}
			else if (line.substr(0, 2).compare("f ") == 0)
			{
				faceLine = i;
				break;
			}
		}

		std::vector<GLint> indices;
		std::vector<GLfloat> orderedTextureCoords = std::vector<GLfloat>(unorderedTextureCoords.size());
		std::vector<GLfloat> orderedNormals = std::vector<GLfloat>(unorderedNormals.size());

		std::vector<std::string> faceString;
		std::vector<GLint> faces;

		for (GLuint i = faceLine; i < modelFile.size(); ++i)
		{
			std::string line = modelFile.at(i).substr(2);

			StringUtil::splitString(line, SPACE_DELIMITER, faceString);

			for (GLuint j = 0; j < faceString.size(); ++j)
			{
				getIntsFromString(faceString.at(j), faces, 0, 3, SLASH_DELIMITER);

				indices.push_back(faces[0]);
				orderedTextureCoords.push_back(unorderedTextureCoords.at(faces[1] * 2));
				orderedTextureCoords.push_back(unorderedTextureCoords.at(faces[1] * 2 + 1));
				orderedNormals.push_back(unorderedNormals.at(faces[2] * 3));
				orderedNormals.push_back(unorderedNormals.at(faces[2] * 3 + 1));
				orderedNormals.push_back(unorderedNormals.at(faces[2] * 3 + 2));

				/*logger.log(Logger::Level::LEVEL_DEBUG, 
					"PI: " + std::to_string(faces[0]) + ": " +
					" P: " + std::to_string(unorderedPositions.at(faces[0] * 3)) + ", " +
							std::to_string(unorderedPositions.at(faces[0] * 3 + 1)) + ", " +
							std::to_string(unorderedPositions.at(faces[0] * 3 + 2)) + 
					" TI: " + std::to_string(faces[1]) + ": " +
					" T: " + std::to_string(unorderedTextureCoords.at(faces[1] * 2)) + ", " +
							std::to_string(unorderedTextureCoords.at(faces[1] * 2 + 1)) +
					" NI: " + std::to_string(faces[2]) + ": " +
					" N: " + std::to_string(unorderedNormals.at(faces[2] * 3)) + ", " +
					std::to_string(unorderedNormals.at(faces[2] * 3 + 1)) + ", " +
					std::to_string(unorderedNormals.at(faces[2] * 3 + 2)));*/

				faces.clear();
			}
			faceString.clear();
		}

		if (unorderedPositions.size() > 0)
		{
			addBufferData(new VertexBufferWrapper(VertexBufferWrapper::BufferType::POSITIONS, unorderedPositions, 3));
		}

		if (orderedTextureCoords.size() > 0)
		{
			addBufferData(new VertexBufferWrapper(VertexBufferWrapper::BufferType::TEXTURE_COORDS, orderedTextureCoords, 2));
		}

		if (orderedNormals.size() > 0)
		{
			addBufferData(new VertexBufferWrapper(VertexBufferWrapper::BufferType::NORMALS, orderedNormals, 3));
		}

		if (indices.size() > 0)
		{
			setElementBuffer(new ElementBufferWrapper(indices));
		}

		mVertexArray = new VertexArrayWrapper();

		prepareMesh();
	}


	void ResourceMesh::unload()
	{
		clearBufferData();

		if (mElementBufferData != nullptr)
		{
			delete mElementBufferData;
		}

		if (mVertexArray != nullptr)
		{
			delete mVertexArray;
		}
	}


	void ResourceMesh::setElementBuffer(ElementBufferWrapper* wrapper)
	{
		mElementBufferData = wrapper;
	}


	void ResourceMesh::addBufferData(VertexBufferWrapper* bufferData)
	{
		mVertexBufferList->push_back(bufferData);
	}


	VertexArrayWrapper* const ResourceMesh::getVertexArray() const
	{
		return mVertexArray;
	}


	VertexBufferWrapper* const ResourceMesh::getVertexBufferWrapper(const VertexBufferWrapper::BufferType& BUFFER_TYPE) const
	{
		for (GLuint i = 0; i < mVertexBufferList->size(); ++i)
		{
			if (mVertexBufferList->at(i)->mBUFFER_TYPE == BUFFER_TYPE)
			{
				return mVertexBufferList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_ERROR, "This model does not have that buffer type.");
		return nullptr;
	}


	ElementBufferWrapper* const  ResourceMesh::getElementBufferData() const
	{
		return mElementBufferData;
	}


	void ResourceMesh::prepareMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Binding VAO: " + std::to_string(mVertexArray->getId()));
		mVertexArray->bind();

		logger.log(Logger::Level::LEVEL_DEBUG, "Binding EBO: " + std::to_string(mElementBufferData->getId()));
		mElementBufferData->bind();

		for (GLuint i = 0; i < mVertexBufferList->size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Binding VBO: " + std::to_string(mVertexBufferList->at(i)->getId()));
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


	void ResourceMesh::addFloatsFromString(std::string line, std::vector<GLfloat>& data, GLuint begin, GLuint amountOfFloats, const char DELIMITER)
	{
		GLint end;
		GLfloat floatVar;

		//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + line.substr(begin));
		//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + std::to_string(line.substr(begin).find_first_of(DELIMITER)));

		for (GLuint i = 0; i < amountOfFloats; ++i)
		{
			end = line.substr(begin).find_first_of(DELIMITER) + begin;
			//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + line.substr(begin, end - begin));
			floatVar = std::stof(line.substr(begin, end - begin));
			//logger.log(Logger::Level::LEVEL_DEBUG, "Adding float: " + std::to_string(floatVar) + " to model data.");
			data.push_back(floatVar);

			begin = end + 1;
		}
	}


	void ResourceMesh::getIntsFromString(std::string line, std::vector<GLint>& data, GLuint begin, GLuint amountOfInts, const char DELIMITER)
	{
		GLint end;
		GLint intVar;

		//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + line.substr(begin));
		//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + std::to_string(line.substr(begin).find_first_of(DELIMITER)));

		for (GLuint i = 0; i < amountOfInts; ++i)
		{
			end = line.substr(begin).find_first_of(DELIMITER) + begin;
			//logger.log(Logger::Level::LEVEL_DEBUG, ":::" + line.substr(begin, end - begin));
			intVar = std::stoi(line.substr(begin, end - begin)) - 1;
			//logger.log(Logger::Level::LEVEL_DEBUG, "Adding float: " + std::to_string(intVar) + " to model data.");
			data.push_back(intVar);

			begin = end + 1;
		}
	}


	void ResourceMesh::render(const GLdouble& DELTA_TIME)
	{
		mVertexArray->bind();
		//glDrawArrays(GL_TRIANGLES, 0, mElementBufferData->getIndiceCount() * 3);
		glDrawElements(GL_TRIANGLES, mElementBufferData->getIndiceCount(), GL_UNSIGNED_INT, 0);
		mVertexArray->unbind();
	}
}