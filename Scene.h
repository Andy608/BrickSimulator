#pragma once
#ifndef BOUNTIVE_SCENE_H_
#define BOUNTIVE_SCENE_H_

#include <glew.h>
#include <string>

namespace Bountive
{
	class Window;

	class Scene
	{
	public:
		const GLint mID;

		Scene(const Window& WINDOW_HANDLE, GLint id, std::string name);
		virtual ~Scene();

		virtual void update(const GLdouble& DELTA_TIME) = 0;
		virtual void render(const GLdouble& DELTA_TIME) = 0;

		const std::string& getName() const;
		
	protected:
		const Window& mWINDOW_HANDLE;
		const std::string mNAME;
	};
}

#endif