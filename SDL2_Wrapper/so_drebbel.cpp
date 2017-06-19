#include <memory>
#include <array>
#include <glm\glm.hpp>
#include "scene_graph.h"
#include "so_includes.h"
#include "a_asset_pack.h"
#include "animation.h"

namespace Environment
{
	namespace Object
	{
		//std::shared_ptr<Utilities::Animation> an;
		DrebbelSub::DrebbelSub(const Assets::AssetPack & pack,
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

			const auto & potentialTexture = pack.textures.find(key);
			if (potentialTexture != pack.textures.end())
				texture(potentialTexture->second);

			//2. generate sub assets
			//2.1 make animations... const auto & archtype = pack.archtype;
			Utilities::Animation fig8Animation(
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::COS,
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
				Utilities::Animation::FN::SIN,
				1.00f, //approx half pi
				3.14f,
				false
				}
			);
			Utilities::Animation fig8AnimationInverted(
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::COS,
				1.00f, //approx half pi
				-3.14f,
				true
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::NONE,
				0.0f,
				0.0f,
				false
			},
				Utilities::Animation::AxConfig{
				Utilities::Animation::FN::SIN,
				1.00f, //approx half pi
				-3.14f,
				true
			}
			);
			//an = std::shared_ptr<Utilities::Animation>( new Utilities::Animation(starboardOarAnimation));
			//2.2 initialise sub assets. 
			//Port
			const std::string oarKey = "oar";
			std::string lKey = "oar_fwd_port";
			mFwdPortOar = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(lKey).offset,
					pack.archtype.adjustment(lKey).orientation,
					pack.archtype.adjustment(lKey).scale,
					fig8AnimationInverted,
					oarKey));
			lKey = "oar_aft_port";
			mAftPortOar = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(lKey).offset,
					pack.archtype.adjustment(lKey).orientation,
					pack.archtype.adjustment(lKey).scale,
					fig8AnimationInverted,
					oarKey));
			//Starboard
			lKey = "oar_fwd_star";
			mFwdStarboardOar = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(lKey).offset,
					pack.archtype.adjustment(lKey).orientation,
					pack.archtype.adjustment(lKey).scale,
					fig8Animation,
					oarKey));
			lKey = "oar_aft_star";
			mAftStarboardOar = std::unique_ptr<AnimatedPart>
				(new AnimatedPart(pack,
					pack.archtype.adjustment(lKey).offset,
					pack.archtype.adjustment(lKey).orientation,
					pack.archtype.adjustment(lKey).scale,
					fig8Animation,
					oarKey));
		}

		void 
		DrebbelSub::simulate(const double deltaTime)
		{
			//sgCoordinateFrame()->transform(an->frame(deltaTime));
			AI_Entity::simulate(deltaTime);
			mAftPortOar->simulate(deltaTime);
			mAftStarboardOar->simulate(deltaTime);
			mFwdPortOar->simulate(deltaTime);
			mFwdStarboardOar->simulate(deltaTime);
			//mStarboard.AftFins->simulate(deltaTime);
			//mStarboard.ForwardFins->simulate(deltaTime);
			//mFwdPortOar->simulate(deltaTime);
			//mStarboard.ForwardOar->simulate(deltaTime);
			//mPort.AftFins->simulate(deltaTime);
			//mPort.ForwardFins->simulate(deltaTime);
			//mPort.AftOar->simulate(deltaTime);
			//mPort.ForwardOar->simulate(deltaTime);
			//mRudder->simulate(deltaTime);
			return;
		}

		void 
		DrebbelSub::buildSceneEntry(
			const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target); //build root system.
			//generate geometry node
			const std::shared_ptr<SG_Geometry> geom(new SG_Geometry(mesh()));
			geom->material(material());
			geom->texture(texture());

			pairSGNodes(geom, sgCoordinateFrame());
			mFwdPortOar->buildSceneEntry(sgCoordinateFrame());
			mFwdStarboardOar->buildSceneEntry(sgCoordinateFrame());
			mAftPortOar->buildSceneEntry(sgCoordinateFrame());
			mAftStarboardOar->buildSceneEntry(sgCoordinateFrame());
		}
	}
}