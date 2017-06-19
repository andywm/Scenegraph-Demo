#include <memory>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <cmath>
#include <ctime>
#include <stdlib.h> 
#include "so_includes.h"
#include "a_asset_pack.h"
#include "random_number.h"

namespace Environment
{
	namespace Object
	{
		AI_Entity::AI_Entity(const glm::vec3 & pos, const glm::vec3 & rot,
			const glm::vec3 & scl)
			:
			Base(pos, rot, scl),
			mHasDestination(false),
			mTakeAvoidanceAction(false)
		{}

		
		void
		AI_Entity::collisionCheck(const std::shared_ptr<Base> other)
		{
			const auto otherpos = other->position();
			const auto mypos = position();

			const auto delta = otherpos - mypos;

			if (glm::abs(glm::length(delta)) < 15)
			{
				mTakeAvoidanceAction = true;
			}
			else mTakeAvoidanceAction = false;
		}

		void
		AI_Entity::think()
		{
			if (mHasDestination || mTakeAvoidanceAction)
			{
				if (fabs(glm::length(position()) -
					glm::length(mTargetVector)) < 10.0f)
				{
					mHasDestination = false;
				}
			}
			else
			{
				mHasDestination = true;
				const float sizeOfSphere = 70.0f;
				//srand(time(nullptr));
				const float x =
					Utilities::random(-sizeOfSphere, sizeOfSphere);
				const float y =
					Utilities::random(-sizeOfSphere, sizeOfSphere);
				const float z =
					Utilities::random(-sizeOfSphere, sizeOfSphere);
				mTargetVector = glm::vec3(x, y, z);
				mDirection = 
					glm::normalize(mTargetVector - position());
			}
		}


		//maybe each axis needs to be resolved differently?
		//so largest value remains the same, where as the speed of the slowest
		//ones are divided by that size...
		void 
		AI_Entity::simulate(const double deltaTime)
		{
			think();
	
			rotation(glm::vec3(0,
				-atan2(mTargetVector.x, mTargetVector.z),
				atan2(mTargetVector.x, mTargetVector.y)));
			position(position() + (mDirection*static_cast<float>(deltaTime)));
			sgCoordinateFrame()->transform(computeTransform());
		}
	}
}
