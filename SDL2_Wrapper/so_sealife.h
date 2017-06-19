#pragma once
#include <memory>
#include <glm\glm.hpp>
#include "scene_graph.h"
#include "so_includes.h"
#include "a_asset_pack.h"

namespace Environment
{
	namespace Object
	{
		class Sealife : public AI_Entity
		{
		public:
			explicit Sealife(const Assets::AssetPack & pack,
				const glm::vec3 & pos,
				const glm::vec3 & rot,
				const glm::vec3 & scl);
			Sealife& operator=(const Sealife &) = delete;
			~Sealife() = default;
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target) override;
		private:
			const std::string mPack;
			std::unique_ptr<AnimatedPart> mLeftFin;
			std::unique_ptr<AnimatedPart> mRightFin;
		};
	}
}