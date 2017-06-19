#include <string>
#include <memory>
#include <sstream> 
#include "environment.h"
#include "Registry.h"
#include "uv_sphere_generator.h"
#include "so_includes.h"

namespace Environment
{

	Environment::Environment(std::shared_ptr<Assets::Registry> reg)
		:
		mAssetRegistry(reg),
		mScene(new Render::Scene::Scene()),
		mRadialLimit(0)
	{}


	/*
		initialises definite world objects with default values, then overrides
		those values if the worldConfig list says so. Then commits them to the
		world.

		loads in all items from the worldAssets list. Adds them to the entities
		list.
	*/
	void
	Environment::generateWorld()
	{
		//demolish existing world
		clearSimulationObjects();
		clearScene();
		
		//int defaultCamera = 0;
		//int linearSpeed = 1, rotationalSpeed = 1;
		auto & worldConfig = mAssetRegistry->worldConfig();

		//make free cameras...
		auto & cams = worldConfig.cameraConfigs();
		for (auto & cam : cams)
		{
			const auto ccam = mScene->makeCamera(cam.position, 
				static_cast<glm::vec2>(cam.orientation), 
				Object::Camera::MODE::FREE, 
				1,
				1);
			ccam->buildSceneEntry(mScene->sceneRoot());
		}
		//make fixed camera...
		const auto ccam = mScene->makeCamera(glm::vec3(0),
			glm::vec2(0),
			Object::Camera::MODE::FOLLOW,
			1,
			1);
		ccam->buildSceneEntry(mScene->sceneRoot());

		auto & spawnList = worldConfig.worldAssets();
		
		for (auto & item : spawnList)
		{
			if (item.makeA == "drebbelsub")
			{
				mSimEntities.push_back(std::shared_ptr<Object::DrebbelSub>
					(new Object::DrebbelSub(
						*item.pack,
						item.position,
						item.orientation,
						item.scale)));
				
			}
			else if (item.makeA == "explorersub")
			{
				mSimEntities.push_back(std::shared_ptr<Object::ExplorerSub>
					(new Object::ExplorerSub(
						*item.pack,
						item.position,
						item.orientation,
						item.scale)));
			}
			else if (item.makeA == "sealife")
			{
				mSimEntities.push_back(std::shared_ptr<Object::Sealife>
					(new Object::Sealife(
						*item.pack,
						item.position,
						item.orientation,
						item.scale)));
			}
			else if (item.makeA == "sphere")
			{
				mSimEntities_Static.push_back(std::shared_ptr<Object::Scenery>
					(new Object::Scenery(
						*item.pack,
						item.position,
						item.orientation,
						item.scale,
						"sphere")));
			}

		}
		//build and inject.
		for (const auto & entity : mSimEntities)
		{
			entity->buildSceneEntry(mScene->sceneRoot());
		}
		//build and inject.
		for (const auto & entity : mSimEntities_Static)
		{
			entity->buildSceneEntry(mScene->sceneRoot());
		}

		mScene->activateCamera(worldConfig.defaultCamera());
	}

	void
	Environment::clearSimulationObjects()
	{
		//design note... this could be potentially dangerous if anything else is
		//allowed to keep a handle to either a sim object or SGNode.
		mSimEntities.clear();
		mSimEntities_Static.clear();
	}

	void
	Environment::clearScene()
	{
		mScene->destroySceneGraph();
	}

	std::shared_ptr<Render::Scene::Scene>
	Environment::scene() const
	{
		return mScene;
	}

	void
	Environment::advanceTime(const double deltaTime) const
	{
		for (const auto & entity : mSimEntities)
		{
			for (const auto & other : mSimEntities)
			{
				if (&other == &entity) continue;

				entity->collisionCheck(other);
			}
			for (const auto & other : mSimEntities_Static)
			{
				entity->collisionCheck(other);
			}

			entity->simulate(deltaTime);
		}
		mScene->camera()->simulate(0);
	}

	void
	Environment::focusPrior() const
	{
		return;
	}

	void
	Environment::focusNext()
	{
		mScene->activateCamera(2);
		const auto & cam = mScene->camera();
		if (static_cast<unsigned int>(cam->focus() + 1)
			< mSimEntities.size())
		{
			cam->focus(cam->focus() + 1);
		}
		else
			cam->focus(0);

		mScene->inject(mSimEntities[cam->focus()]);
	}

	void
	Environment::activateCamera(const int cam)
	{
		mScene->activateCamera(cam);
	}
}