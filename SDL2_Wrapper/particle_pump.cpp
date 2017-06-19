#include <array>
#include <memory>
#include "so_includes.h"
#include "random_number.h"

namespace Environment
{
	namespace Object
	{
		ParticlePump::ParticlePump(const Assets::AssetPack & assets,
			const glm::vec3 & pos, const glm::vec3 & rot,
			const glm::vec3 & scl, const std::string & id)
			:
			Base(pos, rot, scl)
		{
			for (auto & particle : mParticles)
			{
				const auto p2 = glm::vec3(Utilities::random(-5, +2),
					Utilities::random(-2, +2),
					Utilities::random(-2, +2));
				particle = std::shared_ptr<Particle>(
					new Particle(assets, p2, rot, scl, id));
			}
		}

		void
		ParticlePump::buildSceneEntry(
				const std::shared_ptr<SG_Base> target)
		{
			Base::buildSceneEntry(target);
			for (const auto & particle : mParticles)
			{
				particle->buildSceneEntry(sgCoordinateFrame());
			}
		}

		void 
		ParticlePump::simulate(const double deltaTime)
		{
			for (const auto & particle : mParticles)
			{
				particle->simulate(deltaTime);
			}
		}
	}
}

