#include <array>
#include <memory>
#include "so_includes.h"
#include "random_number.h"

namespace Environment
{
	namespace Object
	{
		ParticlePump::Particle::Particle(const Assets::AssetPack & pack,
			const glm::vec3 & pos, const glm::vec3 & rot,
			const glm::vec3 & scl, const std::string & id)
			:
			Base(pos, rot, scl)
		{
			const auto & potentialMesh = pack.meshes.find(id);
			if (potentialMesh != pack.meshes.end())
				mesh(potentialMesh->second);

			const auto & potentialMaterial = pack.materials.find(id);
			if (potentialMaterial != pack.materials.end())
				material(potentialMaterial->second);

			const auto & potentialTexture = pack.textures.find(id);
			if (potentialTexture != pack.textures.end())
				texture(potentialTexture->second);
		}

		void 
		ParticlePump::Particle::simulate(const double deltaTime)
		{
			glm::vec3 newPos(position().x-
				Utilities::random(1,10)*deltaTime,
				position().y,position().z);
			if (newPos.x < -8)
			{
				newPos.x = 0;
				newPos.y = Utilities::random(-1.5f, 1.5f);
				newPos.z = Utilities::random(-1.5f, 1.5f);
			}
			position(newPos);
			sgCoordinateFrame()->transform(computeTransform());
		}

		void
		ParticlePump::Particle::buildSceneEntry(
				const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target);
			//generate geometry node
			const std::shared_ptr<SG_Geometry> 
				geom(new SG_Geometry(mesh()));
			geom->material(material());
			geom->texture(texture());

			pairSGNodes(geom, sgCoordinateFrame());
		}
	}
}

