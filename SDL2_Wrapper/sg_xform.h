#pragma once
#include <memory>
#include <vector>
#include "visitor_base.h"
#include "sg_base.h"
#include "sg_group.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Xform final: public Group
			{
			public:
				explicit Xform(const glm::mat4 & trans);
				~Xform() = default;

				/*
				const glm::mat4 & translation();
				void translation (const glm::mat4 & t);
				const glm::mat4 & rotation();
				void rotation(const glm::mat4 & r);
				const glm::mat4 & scale();
				void scale(const glm::mat4 & s);
				*/
				inline const glm::mat4 &
				Xform::transform() const
				{
					return mTransform;
				}

				inline void
				Xform::transform(const glm::mat4 & t)
				{
					mTransform = t;
				}

			private:
				static IDENTITY defaultIdentity;
				//glm::mat4 mScale;
				//glm::mat4 mRotation;
				//glm::mat4 mTranslation;
				glm::mat4 mTransform;
			};
		}
	}
}