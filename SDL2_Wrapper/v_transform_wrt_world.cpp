#pragma once
#include <stack>
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			void
			WorldTransform::visit(SGBase * const node) const
			{
				//reset identity.
				mResultantWorldTransform = glm::mat4(1);

				if (node->isA(IDENTITY::XFORM))
				{
					mTransform.push(static_cast<Xform*>(node)->transform());
				}
				if (node->parent() != nullptr)
				{
					visit(node->parent().get());
				}
			}

			const glm::mat4 &
			WorldTransform::transform() 
			{
				while (!mTransform.empty())
				{
					mResultantWorldTransform = mResultantWorldTransform *
						mTransform.top();
					mTransform.pop();
				}
				return mResultantWorldTransform;
			}
		}
	}
}
