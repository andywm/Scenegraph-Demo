#pragma once
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Injector : public VBase
			{
			public:
				Injector(std::shared_ptr<SGBase> target, 
					std::shared_ptr<SGBase> current);
				virtual ~Injector() = default;
				virtual void visit(SGBase * const node) const override;
			private:
				mutable std::shared_ptr<SGBase> mTarget;
				mutable std::shared_ptr<SGBase> mCurrent;
			};
		}
	}
}
