#pragma once
#include "so_includes.h"
#include "scene_graph.h"
/*
namespace Environment
{
	namespace Object
	{
		class LightSource : public Base
		{
		public:
			struct Properties
			{
				glm::vec4 diffuseColour;
				glm::vec4 specularColour;
				glm::vec4 ambientColour;
			};
			//make a directional light
			explicit LightSource(const Properties & properties,
				const glm::vec3 direction);
			//make a point light
			explicit LightSource(const Properties & properties,
				const glm::vec3 position, float attenuation);
			//make a spot light
			explicit LightSource(const Properties & properties,
				const glm::vec3 position, const glm::vec3 direction,
				float attenuation, float halfArc, float exponent);
			~LightSource()=default;
			virtual void simulate(const double deltaTime);
			virtual void buildSceneEntry(std::shared_ptr<SG_Base> target);
			void enable();
			void disable();
		private:
			//shared_ptr<LightSource> SG_Light;
			glm::vec3 mPosition;
			glm::vec3 mDirection;
			float mAttenuation, mExponent, mHalfArc;
			enum class TYPE { POINT, SPOT, DIRECTIONAL } mType;
		};
	}
}
*/