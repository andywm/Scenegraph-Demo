#pragma once
#include <memory>
#include <vector>
#include <array>
#include <glm\glm.hpp>
#include "archtype.h"
#include "Registry.h"
#include "a_asset_pack.h"

namespace Assets
{
	class WorldConfig
	{
	public:
		struct CameraConfig
		{
			glm::vec3 position;
			glm::vec3 orientation;
		};
		struct WorldAsset
		{
			std::string makeA;
			std::shared_ptr<AssetPack> pack;
			glm::vec3 position;
			glm::vec3 orientation;
			glm::vec3 scale;
		};
		WorldConfig() = default;
		~WorldConfig() = default;

		const std::vector<WorldAsset> & worldAssets() const;
		void worldAsset(const WorldAsset & wa);
		const std::array<CameraConfig, 2> & cameraConfigs() const;
		void cameraConfig(const CameraConfig & ca, const int cam);
		const float sphereSize() const;
		void sphereSize(const float size);
		const float sphereResolution() const;
		void sphereResolution(const float res);
		const int defaultCamera() const;
		void defaultCamera(const int cam);

	private:
		float mSphereSize;
		float mSphereResolution;
		int mDefaultCamera;
		std::array<CameraConfig, 2> mCameras;
		std::vector<WorldAsset> mWorldAssets;
	};
}