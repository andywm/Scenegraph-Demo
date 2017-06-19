#pragma once
#include "scene_graph.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			Injector::Injector(std::shared_ptr<SGBase> target,
			std::shared_ptr<SGBase> current)
				:
				mTarget(target),
				mCurrent(current)
			{
				//std::shared_ptr<SGBase> cParent = mCurrent->parent();
				target->accept(this);
			}

			void
			Injector::visit(SGBase * const node) const
			{
				/*
				if (node->isA(IDENTITY::GROUP))
				{
					auto children = static_cast<Group*>(node)->children();
					mTarget = children[0];
					mTarget->accept(this);
				}*/
				if (node->isA(IDENTITY::XFORM))
				{
					const auto par = mCurrent->parent().get();
					static_cast<Group*>(par)->remove(mCurrent);
					static_cast<Xform*>(node)->add(mCurrent, mTarget);
				}
			}
		}
	}
}
