#pragma once
#include <memory>
#include "sg_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class SGBase; //fwd dec
			class VBase
			{
			public:
				VBase() {}
				virtual ~VBase() {}
				virtual void visit(SGBase * const) const = 0;
			};
		}
	}
}