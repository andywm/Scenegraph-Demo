#pragma once
#include <queue>
#include <stack>
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class WorldTransform
			{
			public:
				WorldTransform() = default;
				virtual ~WorldTransform() = default;
				virtual void visit(SGBase * const node) const;
				const glm::mat4 & transform();
			private:
				mutable std::stack<glm::mat4> mTransform;
				mutable glm::mat4 mResultantWorldTransform;
			};
		}
	}
}
