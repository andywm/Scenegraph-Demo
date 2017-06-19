#pragma once
#include <memory>
#include <vector>
#include "visitor_base.h"
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Orphanise : public DFS
			{
			public:
				Orphanise() = default;
				~Orphanise() = default;
				virtual void visit(SGBase * const node) const override;				
			};

		}
	}
}