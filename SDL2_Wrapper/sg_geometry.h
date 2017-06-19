#pragma once
#include <memory>
#include <vector>
#include "mesh.h"
#include "material.h"
#include "image.h"
#include "visitor_base.h"
#include "sg_base.h"
#include "sg_group.h"

namespace Render
{
	namespace Scene
	{
		namespace Graph
		{
			class Geometry final : public SGBase
			{
			public:
				explicit Geometry(std::shared_ptr<Assets::Mesh> m);
				~Geometry() = default;

				inline const std::shared_ptr<Assets::Mesh> 
				mesh() const
				{
					return mMesh;
				}

				inline const std::shared_ptr<Assets::Material>
				material() const
				{
					return mMaterial;
				}

				inline void 
				material(const std::shared_ptr<Assets::Material> mat)
				{
					mMaterial = mat;
				}

				inline const std::shared_ptr<Assets::Image>
				texture() const
				{
					return mTexture;
				}

				inline void
				texture(const std::shared_ptr<Assets::Image> img)
				{
					mTexture = img;
				}

			private:
				static IDENTITY defaultIdentity;
				std::shared_ptr<Assets::Mesh> mMesh;
				std::shared_ptr<Assets::Material> mMaterial;
				std::shared_ptr<Assets::Image> mTexture;
			};
		}
	}
}