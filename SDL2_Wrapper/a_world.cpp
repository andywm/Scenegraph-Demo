#include <memory>
#include <vector>
#include <array>
#include <glm\glm.hpp>
#include "archtype.h"
#include "Registry.h"
#include "a_world.h"
namespace Assets
{
	const std::vector<WorldConfig::WorldAsset> &
	WorldConfig::worldAssets() const
	{
		return mWorldAssets;
	}

	void 
	WorldConfig::worldAsset(const WorldAsset & wa)
	{
		mWorldAssets.push_back(wa);
	}

	const std::array<WorldConfig::CameraConfig, 2> &
	WorldConfig::cameraConfigs() const
	{
		return mCameras;
	}

	void
	WorldConfig::cameraConfig(const CameraConfig & cc, const int cam)
	{
		mCameras[cam] = cc;
	}

	const float 
	WorldConfig::sphereSize() const
	{
		return mSphereSize;
	}

	void 
	WorldConfig::sphereSize(const float size)
	{
		mSphereSize = size;
	}

	const float
	WorldConfig::sphereResolution() const
	{
		return mSphereResolution;
	}

	void 
	WorldConfig::sphereResolution(const float res)
	{
		mSphereResolution = res;
	}

	const int
	WorldConfig::defaultCamera() const
	{
		return mDefaultCamera;
	}

	void 
	WorldConfig::defaultCamera(const int cam)
	{
		mDefaultCamera = cam;
	}
}