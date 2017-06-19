#include <memory>
#include "v_dfs.h"
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			void 
			DFS::visit(SGBase * const node) const
			{
				if (node->isA(IDENTITY::GROUP) || node->isA(IDENTITY::XFORM))
				{
					auto children = static_cast<Group*>(node)->children();

					for (const auto & child : children)
					{
						child->accept(this);
					}
				}
			}
		}
	}
}