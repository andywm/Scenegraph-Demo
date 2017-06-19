#include <memory>
#include <vector>
#include <glm\glm.hpp>
#include "mesh.h"
#include "visitor_base.h"
#include "sg_base.h"
#include "sg_group.h"
#include "sg_camera.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			IDENTITY Camera::defaultIdentity = IDENTITY::CAMERA;
			Camera::Camera() 
				:
				mActive(false)
			{
				reidentifyAs(defaultIdentity);
			}	
		}
	}
}