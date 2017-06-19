#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Assets
{
	class Material
	{
	private:
		glm::vec4 mDiffuse;
		glm::vec4 mAmbient;
		glm::vec4 mSpecular;
		float mSpecularExponent;

	public:
		explicit Material(const std::string & dotObjFile);
		Material() = default;

		inline const glm::vec4 &
		diffuse() const
		{
			return mDiffuse;
		}

		inline const glm::vec4  &
		ambient() const
		{
			return mAmbient;
		}

		inline const glm::vec4 &
		specular() const
		{
			return mSpecular;
		}

		inline const float 
		specularExponent() const
		{
			return mSpecularExponent;
		}

	};
}