#pragma once

#include <memory>
#include "visitor_base.h"
#include "sg_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class DFS : public VBase
			{
			public:
				DFS() = default;
				~DFS() = default;
				virtual void visit(SGBase * const node) const override;
			};

		}
	}
}