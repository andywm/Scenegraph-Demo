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
			class Linearise : public DFS
			{
			public:
				explicit Linearise(std::shared_ptr<SGBase> node);
				Linearise& operator=(const Linearise&) = delete;
				Linearise(const Linearise &) = delete;
				~Linearise() = default;
				virtual void visit(SGBase * const node) const override;
				Graph::Camera * viewInformation() const;

				//inlined...
				inline const std::vector<SGBase *> &
				linearised() const
				{
					return mLinear;
				}
				
			private:
				//aw, need intrusive_ptrs...
				mutable std::vector<SGBase *> mLinear;
				mutable Graph::Camera * mView;
			};

		}
	}
}