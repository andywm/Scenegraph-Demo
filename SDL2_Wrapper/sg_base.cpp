#include <memory>
#include <glm/glm.hpp>
#include "visitor_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{	
			IDENTITY SGBase::defaultIdentity = IDENTITY::BASE;
			SGBase::SGBase()
				:
				mIsA(defaultIdentity)
			{}

			void
			SGBase::accept(const VBase * const v)
			{
				v->visit(this);
			}

			bool
			SGBase::isA(const IDENTITY id) const
			{
				return mIsA == id;
			}

			void
			SGBase::reidentifyAs(const IDENTITY id)
			{
				mIsA = id;
			}
		}
	}
}