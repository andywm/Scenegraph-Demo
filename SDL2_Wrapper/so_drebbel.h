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
		class DrebbelSub : public AI_Entity
		{
		public:
			explicit DrebbelSub(const Assets::AssetPack & pack,
				const glm::vec3 & pos,
				const glm::vec3 & rot,
				const glm::vec3 & scl);
			~DrebbelSub() = default;
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target) override;
		private:
			std::unique_ptr<AnimatedPart> mFwdPortOar;
			std::unique_ptr<AnimatedPart> mFwdStarboardOar;
			std::unique_ptr<AnimatedPart> mAftPortOar;
			std::unique_ptr<AnimatedPart> mAftStarboardOar;
		};
	}
}