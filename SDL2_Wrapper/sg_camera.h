#pragma once
#include <memory>
#include <vector>
#include "mesh.h"
#include "visitor_base.h"
#include "sg_base.h"
#include "sg_group.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Camera final : public SGBase
			{
			public:
				Camera();
				~Camera() = default;

				inline const glm::mat4
				Camera::view(const glm::mat4 & world) const
				{
					return glm::inverse(world);
				}

				inline const glm::mat4 &
				Camera::projection() const
				{
					return mPerspectiveProjection;
				}

				inline void
				Camera::projection(const glm::mat4 & t)
				{
					mPerspectiveProjection = t;
				}

				inline const glm::mat4 &
				Camera::orientation() const
				{
					return mDetachedOrientation;
				}

				inline void
				Camera::orientation(const glm::mat4 & orient)
				{
					mDetachedOrientation = orient;
				}

				inline void
				Camera::deactivate()
				{
					mActive = false;
				}

				inline void
				Camera::activate()
				{
					mActive = true;
				}

				inline bool
				Camera::active() const
				{
					return mActive;
				}
			private:				
				bool mActive;
				glm::mat4 mDetachedOrientation;
				glm::mat4 mPerspectiveProjection;
				static IDENTITY defaultIdentity;
			};
		}
	}
}