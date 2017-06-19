#pragma once
#include <memory>
#include <glm\glm.hpp>

namespace Environment
{
	namespace Object
	{
		class AI_Entity : public Base
		{
		public:
			AI_Entity(const glm::vec3 & pos, const glm::vec3 & rot, 
				const glm::vec3 & scl);
			~AI_Entity() = default;

			void collisionCheck(std::shared_ptr<Base> other);
			//virtual void simulate(const double deltaTime) = 0;
			//virtual void buildSceneEntry(const glm::vec3 & p) = 0;

			//for pathing
			/*
			adjust target to be world origin
			assuming all objects are in world space
			targetVector = target - self
			targetVector = targetVector.normalised();

			as long as the magnitude > "a threshold"
			proceccede to target
			*/

			void simulate(const double deltaTime) override;

		protected:
			void think();

		private:
			bool mTakeAvoidanceAction;
			std::shared_ptr<SG_Camera> mCamera;
			//bool mReorient;
			bool mHasDestination;
			glm::vec3 mTargetVector;
			glm::vec3 mDirection;
		};
	}
}
