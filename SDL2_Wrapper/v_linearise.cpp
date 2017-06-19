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
			Linearise::Linearise(std::shared_ptr<SGBase> node)
				:
				mView(nullptr)
			{
				DFS::visit(node.get());
			}

			void 
			Linearise::visit(SGBase * const node) const
			{
				if (node->isA(IDENTITY::GEOMETRY))
				{
					mLinear.push_back(node);
				}
				else if (node->isA(IDENTITY::CAMERA))
				{
					if(static_cast<Camera *>(node)->active())
					{
						mView = static_cast<Camera *>(node);
					}
				}
				else
				{
					DFS::visit(node);
				}
			}

			Graph::Camera * 
			Linearise::viewInformation() const
			{
				return mView;
			}
		}
	}
}