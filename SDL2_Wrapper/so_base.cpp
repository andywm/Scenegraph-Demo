#pragma once
#include <memory>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "scene_graph.h"
#include "so_base.h"

namespace Environment
{
	namespace Object
	{

		Base::Base(const glm::vec3 & pos, const glm::vec3 & rot,
			const glm::vec3 & scl)
			:
			mBaseTranslation(pos),
			mEulerRotation(rot),
			mScale(scl)
		{
			
		}

		void 
		Base::pairSGNodes(const std::shared_ptr<SG_Base> child,
			const std::shared_ptr <SG_Base> parent) const
		{
			static_cast<SG_Group*>(parent.get())->add(child, parent);
		}
		void 
		Base::injectIntoCS(const std::shared_ptr<SG_Base> obj) const
		{
			Render::Scene::Graph::Injector(sgCoordinateFrame(), obj);
		}
		void
		Base::buildSceneEntry(const std::shared_ptr<SG_Base> target)
		{
			sgLocalRoot(std::shared_ptr<SG_Group>(new SG_Group()));
			
			sgCoordinateFrame(std::shared_ptr<SG_Xform>
				(new SG_Xform(computeTransform())));

			pairSGNodes(sgLocalRoot(), target);
			pairSGNodes(sgCoordinateFrame(), sgLocalRoot());

		}


		const glm::mat4 
		Base::computeTransform() const
		{
			glm::mat4 transform;
			
			transform *= glm::translate(position());
			transform *= glm::rotate(rotation().x, glm::vec3(1, 0, 0));
			transform *= glm::rotate(rotation().y, glm::vec3(0, 1, 0));
			transform *= glm::rotate(rotation().z, glm::vec3(0, 0, 1));
			transform *= glm::scale(scale());

			return transform;
		}
	}
}
