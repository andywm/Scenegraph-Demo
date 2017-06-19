#include <glm\gtx\transform.hpp>
#include "so_includes.h"
#include "animation.h"
#include "scene_graph.h"

namespace Environment
{
	namespace Object
	{
		AnimatedPart::AnimatedPart(
			const Assets::AssetPack & pack, const glm::vec3 & pos, 
			const glm::vec3 & rot, const glm::vec3 & scl,
			const Utilities::Animation & animation, const std::string & id)
			:
			Base(pos, rot, scl),
			mAnimation(animation)
		{
			mInitialOrientation = glm::rotate(rot.x, glm::vec3(1, 0, 0));
			mInitialOrientation *= glm::rotate(rot.y, glm::vec3(0, 1, 0));
			mInitialOrientation *= glm::rotate(rot.z, glm::vec3(0, 0, 1));
			const auto & mainMesh = pack.meshes.find(id);
			if (mainMesh != pack.meshes.end())
				mesh(mainMesh->second);

			const auto & potentialMaterial = pack.materials.find(id);
			if (potentialMaterial != pack.materials.end())
				material(potentialMaterial->second);

			const auto & potentialTexture = pack.textures.find(id);
			if (potentialTexture != pack.textures.end())
				texture(potentialTexture->second);
		}

		void 
		AnimatedPart::simulate(const double deltaTime)
		{
			const auto r = mAnimation.frame(deltaTime);
			const auto rest = computeTransform();

			sgCoordinateFrame()->transform(rest*r);
		}

		void 
		AnimatedPart::buildSceneEntry(
			const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target);


			//generate geometry node
			const std::shared_ptr<SG_Geometry> 
				geom(new SG_Geometry(mesh()));
			geom->material(material());
			geom->texture(texture());
			//pairSGNodes(sgCoordinateFrame(), sgLocalRoot());
			pairSGNodes(geom, sgCoordinateFrame());

			//pairSGNodes(sgLocalRoot(), target);
		}
	}
}