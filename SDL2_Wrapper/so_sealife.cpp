#include <memory>
#include <glm\glm.hpp>
#include "scene_graph.h"
#include "so_includes.h"
#include "a_asset_pack.h"

namespace Environment
{
	namespace Object
	{
		Sealife::Sealife(const Assets::AssetPack & pack,
			const glm::vec3 & pos, const glm::vec3 & rot, const glm::vec3 & scl)
			:
			AI_Entity(pos, rot, scl)
		{
			//make the sub
			//1. get the main hull and textures.
			const std::string key = "fish";

			const auto & potentialMesh = pack.meshes.find(key);
			if (potentialMesh != pack.meshes.end())
				mesh(potentialMesh->second);

			const auto & potentialMaterial = pack.materials.find(key);
			if (potentialMaterial != pack.materials.end())
				material(potentialMaterial->second);

			//2. generate sub assets
			//2.1 make animations... const auto & archtype = pack.archtype;
			Utilities::Animation finAnimation( //fix this name.
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::COS,
				0.5f, //approx half pi
				3.14f,
				false
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::NONE,
				0.0f,
				0.0f,
				false
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::NONE,
				1.00f, //approx half pi
				3.14f,
				false
			}
			);
			Utilities::Animation finAnimationInverted( //fix this name.
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::SIN,
				0.5f, //approx half pi
				3.14f,
				false
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::NONE,
				0.0f,
				0.0f,
				false
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::NONE,
				1.00f, //approx half pi
				3.14f,
				false
			}
			);
			//2.2 initialise sub assets. 
			std::string offsetKey = "left_fin";
			const std::string assetKey = "fin";
			mLeftFin = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(offsetKey).offset,
					pack.archtype.adjustment(offsetKey).orientation,
					pack.archtype.adjustment(offsetKey).scale,
					finAnimation,
					assetKey));
			offsetKey = "right_fin";
			mRightFin = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(offsetKey).offset,
					pack.archtype.adjustment(offsetKey).orientation,
					pack.archtype.adjustment(offsetKey).scale,
					finAnimationInverted,
					assetKey));
		}

		void 
		Sealife::simulate(const double deltaTime)
		{
			AI_Entity::simulate(deltaTime);
			mLeftFin->simulate(deltaTime);
			mRightFin->simulate(deltaTime);
			return;
		}

		void 
		Sealife::buildSceneEntry(
			const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target); //build root system.
			sgLocalRoot(std::shared_ptr<SG_Group>(new SG_Group()));

			//generate geometry node
			const std::shared_ptr<SG_Geometry> 
				geom(new SG_Geometry(mesh()));
			geom->material(material());
			geom->texture(texture());

			pairSGNodes(geom, sgCoordinateFrame());
			//add at specified location in scene...
			mLeftFin->buildSceneEntry(sgCoordinateFrame());
			mRightFin->buildSceneEntry(sgCoordinateFrame());
		}
	}
}