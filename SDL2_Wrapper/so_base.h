#pragma once
#include <memory>
#include <glm\glm.hpp>
#include "scene_graph.h"
#include "Registry.h"

namespace Environment
{
	namespace Object
	{
		using SG_Base  = Render::Scene::Graph::SGBase;
		using SG_Xform = Render::Scene::Graph::Xform;
		using SG_Group = Render::Scene::Graph::Group;
		using SG_Geometry = Render::Scene::Graph::Geometry;
		using SG_Camera = Render::Scene::Graph::Camera; //not used.

		class Base
		{
		private:
			glm::vec3 mBaseTranslation, mEulerRotation, mScale;
			std::shared_ptr<SG_Xform> mCoordinateFrame;
			std::shared_ptr<SG_Group> mLocalSGRoot;
			std::shared_ptr<Assets::Mesh> mBodyMesh;
			std::shared_ptr<Assets::Material> mMaterial;
			std::shared_ptr<Assets::Image> mTexture;

		public:
			Base(const glm::vec3 & pos, const glm::vec3 & rot, 
				const glm::vec3 & scl);
			virtual ~Base() = default;

			virtual void simulate(const double deltaTime) = 0;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target);
			const glm::mat4 computeTransform() const;
			inline std::shared_ptr<SG_Base>
			Base::sgRepresentation() const
			{
				return sgLocalRoot();
			}
			void Base::injectIntoCS(const std::shared_ptr<SG_Base> obj) 
				const;

			inline const glm::vec3 &
				position() const
			{
				return mBaseTranslation;
			}

		protected:
			void pairSGNodes(const std::shared_ptr<SG_Base> element,
				const std::shared_ptr <SG_Base> target) const;

			inline std::shared_ptr<SG_Xform>
			sgCoordinateFrame() const
			{
				return mCoordinateFrame;
			}

			inline std::shared_ptr<SG_Group>
			sgLocalRoot() const
			{
				return mLocalSGRoot;
			}

			

			inline void
			position(const glm::vec3 & pos)
			{
				mBaseTranslation = pos;
			}

			inline const glm::vec3 &
			rotation() const
			{
				return mEulerRotation;
			}

			inline void
			rotation(const glm::vec3 & rot)
			{
				mEulerRotation = rot;
			}

			inline const glm::vec3 &
			scale() const
			{
				return mScale;
			}

			inline void
			scale(const glm::vec3 & scl)
			{
				mScale = scl;
			}

			inline void
			sgCoordinateFrame(const std::shared_ptr<SG_Xform> xform)
			{
				mCoordinateFrame = xform;
			}

			inline void
			sgLocalRoot(const std::shared_ptr<SG_Group> group)
			{
				mLocalSGRoot = group;
			}

			inline const std::shared_ptr<Assets::Mesh>
			mesh() const
			{
				return mBodyMesh;
			}

			inline void
			mesh(const std::shared_ptr<Assets::Mesh> m)
			{
				mBodyMesh = m;
			}

			inline const std::shared_ptr<Assets::Material>
			material() const
			{
				return mMaterial;
			}

			inline void
			material(const std::shared_ptr<Assets::Material> m)
			{
				mMaterial = m;
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
		};
	}
}
