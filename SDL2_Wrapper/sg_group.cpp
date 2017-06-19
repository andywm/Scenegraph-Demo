#include <memory>
#include <vector>
#include "sg_group.h"
#include "visitor_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			IDENTITY Group::defaultIdentity = IDENTITY::GROUP;
			Group::Group()
			{
				//override identity
				reidentifyAs(defaultIdentity);
			}

			void
			Group::add(const std::shared_ptr<SGBase> node,
				const std::shared_ptr<SGBase> self)
			{
				mChildren.push_back(node);
				node->parent(self);
			}
			void 
			Group::remove(const std::shared_ptr<SGBase> node)
			{
				for (auto & it = mChildren.begin(); it!=mChildren.end(); it++)
				{
					if (it->get() == node.get())
					{
						node->parent(nullptr);
						mChildren.erase(it);
						return;
					}
				}
			}

			void 
			Group::clearChildren()
			{
				mChildren.clear();
			}		
		}
	}
}