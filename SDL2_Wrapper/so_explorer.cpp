#include <memory>
#include <glm\glm.hpp>
#include "scene_graph.h"
#include "so_includes.h"
#include "a_asset_pack.h"

namespace Environment
{
	namespace Object
	{
		ExplorerSub::ExplorerSub(const Assets::AssetPack & pack,
			const glm::vec3 & pos, const glm::vec3 & rot, const glm::vec3 & scl)
			:
			AI_Entity(pos, rot, scl)
		{
			//make the sub
			//1. get the main hull and textures.
			const std::string key = "hull";

			const auto & potentialMesh = pack.meshes.find(key);
			if (potentialMesh != pack.meshes.end())
				mesh(potentialMesh->second);

			const auto & potentialMaterial = pack.materials.find(key);
			if (potentialMaterial != pack.materials.end())
				material(potentialMaterial->second);

			//2. generate sub assets
			//2.1 make animations... const auto & archtype = pack.archtype;
			Utilities::Animation propAnimation(
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::LINEAR,
				1.00f, //approx half pi
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
			std::string offsetKey = "prop";
			std::string assetKey = "prop";
			mPropeller = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(offsetKey).offset,
					pack.archtype.adjustment(offsetKey).orientation,
					pack.archtype.adjustment(offsetKey).scale,
					propAnimation,
					assetKey));
			assetKey = "particle";
			offsetKey = "pump";
			mParticles = std::unique_ptr<ParticlePump>
				(new ParticlePump(pack,
					pack.archtype.adjustment(offsetKey).offset,
					pack.archtype.adjustment(offsetKey).orientation,
					pack.archtype.adjustment(offsetKey).scale,
					assetKey));
		}

		void 
		ExplorerSub::simulate(const double deltaTime)
		{
			mPropeller->simulate(deltaTime);
			mParticles->simulate(deltaTime);
		}

		void 
		ExplorerSub::buildSceneEntry(
			const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target); //build root system.
			//generate geometry node
			const std::shared_ptr<SG_Geometry> geom(new SG_Geometry(mesh()));
			geom->material(material());
			geom->texture(texture());

			mParticles->buildSceneEntry(sgCoordinateFrame());
			pairSGNodes(geom, sgCoordinateFrame());
			mPropeller->buildSceneEntry(sgCoordinateFrame());			
		}
	}
}