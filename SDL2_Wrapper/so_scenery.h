#pragma once
#include <string>
#include "so_includes.h"
#include "animation.h"
#include "scene_graph.h"

namespace Environment
{
	namespace Object
	{
		class Scenery : public Base
		{
		public:
			explicit Scenery(const Assets::AssetPack & assets,
				const glm::vec3 & pos, const glm::vec3 & rot,
				const glm::vec3 & scl, const std::string & id);
			~Scenery() = default;
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(const std::shared_ptr<SG_Base> target)
				override;
		};
	}
}
