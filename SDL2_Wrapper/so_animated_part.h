#pragma once
#include "so_includes.h"
#include "animation.h"
#include "scene_graph.h"
#include "a_asset_pack.h"

namespace Environment
{
	namespace Object
	{
		class AnimatedPart : public Base
		{
		public:
			explicit AnimatedPart(const Assets::AssetPack & assets,
				const glm::vec3 & pos, const glm::vec3 & rot,
				const glm::vec3 & scl, const Utilities::Animation & animation,
				const std::string & id);
			~AnimatedPart() = default;
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target) override;
		private:
			Utilities::Animation mAnimation;
			glm::mat4 mInitialOrientation;
		};
	}
}