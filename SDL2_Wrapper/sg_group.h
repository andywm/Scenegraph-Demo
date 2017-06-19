#pragma once
#include <memory>
#include <vector>
#include "visitor_base.h"
#include "sg_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Group : public SGBase
			{
			public:
				Group();
				~Group()=default;
				//void add(std::shared_ptr<SGBase> node);
				void add(const std::shared_ptr<SGBase> node,
					const std::shared_ptr<SGBase> self);
				void remove(const std::shared_ptr<SGBase> node);
				void clearChildren();
				/*returns a shallow copy of the array of children;*/
				inline std::vector<std::shared_ptr<SGBase>> &
				children()
				{
					return mChildren;
				}

			private:
				std::vector<std::shared_ptr<SGBase>> mChildren;
				static IDENTITY defaultIdentity;
			};
		}
	}
}