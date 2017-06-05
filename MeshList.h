#pragma once
#ifndef BOUNTIVE_MESHLIST_H_
#define BOUNTIVE_MESHLIST_H_

namespace Bountive
{
	class ResourceMeshGui;

	class MeshList
	{
	public:
		static ResourceMeshGui** mGuiMesh;

	private:
		MeshList();
	};
}

#endif