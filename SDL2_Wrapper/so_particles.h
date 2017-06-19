#pragma once
#include <array>
#include <memory>
#include "so_includes.h"
#include "random_number.h"
namespace Environment
{
	namespace Object
	{
		class ParticlePump : public Base
		{
		public:
			explicit ParticlePump(const Assets::AssetPack & assets,
				const glm::vec3 & pos, const glm::vec3 & rot,
				const glm::vec3 & scl,const std::string & id);
			~ParticlePump() = default;
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target) override;
		private:
			class Particle : public Base
			{
			public:
				explicit Particle(const Assets::AssetPack & assets,
					const glm::vec3 & pos, const glm::vec3 & rot,
					const glm::vec3 & scl, const std::string & id);
				~Particle() = default;
				virtual void simulate(const double deltaTime) override;
				virtual void buildSceneEntry(
					const std::shared_ptr<SG_Base> target) override;
			};
			std::array<std::shared_ptr<Particle>, 60> mParticles;
		};
	}
}

