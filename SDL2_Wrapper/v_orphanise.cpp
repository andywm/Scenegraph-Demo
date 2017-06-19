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
			void
			Orphanise::visit(SGBase * const node) const 
			{
				DFS::visit(node);
				node->parent(nullptr);
				if (node->isA(IDENTITY::GROUP) || node->isA(IDENTITY::XFORM))
				{
					static_cast<Group*>(node)->clearChildren();
				}
			}
		}
	}
}

