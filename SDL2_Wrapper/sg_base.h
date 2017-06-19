#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "visitor_base.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			enum class IDENTITY { BASE, XFORM, GEOMETRY, GROUP, CAMERA };
			class VBase; //forward declaration
			class SGBase
			{
			public:
				struct Volume
				{
					glm::vec3 min;
					glm::vec3 max;
					bool valid;
				};
				SGBase();
				virtual ~SGBase() {}
				virtual void accept(const VBase * const visit);
				bool isA(const IDENTITY id) const;
				//inlined
				inline void
				parent(const std::shared_ptr<SGBase> node)
				{
					mParent = node;
				}

				inline const std::shared_ptr<SGBase>
				parent() const
				{
					return mParent;
				}

			protected:
				void reidentifyAs(const IDENTITY id);

			private:
				static IDENTITY defaultIdentity; 
				std::shared_ptr<SGBase> mParent;
				IDENTITY mIsA;
		
				//Volume mBoundingBox;
			};
		}
	}
}