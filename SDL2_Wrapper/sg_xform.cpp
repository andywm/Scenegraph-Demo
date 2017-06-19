#include <memory>
#include <vector>
#include <glm\glm.hpp>
#include "visitor_base.h"
#include "sg_base.h"
#include "sg_xform.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			IDENTITY Xform::defaultIdentity = IDENTITY::XFORM;
			Xform::Xform(const glm::mat4 & trans)
				:
				mTransform(trans)
			{
				//override identity
				reidentifyAs(defaultIdentity);
			}
		}
	}
}