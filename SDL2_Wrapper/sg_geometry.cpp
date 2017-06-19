#include <memory>
#include "mesh.h"
#include "sg_geometry.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			IDENTITY Geometry::defaultIdentity = IDENTITY::GEOMETRY;
			Geometry::Geometry(std::shared_ptr<Assets::Mesh> m)
				:
				mMesh(m),
				mMaterial(nullptr)
			{
				reidentifyAs(defaultIdentity);
			}
		}
	}
}