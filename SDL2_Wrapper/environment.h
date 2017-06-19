#pragma once
#include<memory>
#include<string>
#include<vector>
#include "Scene.h"

#include "Registry.h"
#include "so_includes.h"
//#include "so_sphere.h"

namespace Environment
{
	class Environment
	{
	public:
		explicit Environment(std::shared_ptr<Assets::Registry> reg);
		~Environment() = default;

		void generateWorld();
		std::shared_ptr<Render::Scene::Scene> scene() const;
		void advanceTime(double deltaTime) const;
		void focusPrior() const;
		void focusNext();
		void activateCamera(const int cam);

	private:
		float mRadialLimit;
		//std::unique_ptr<Sphere> mSphere;
		std::vector<std::shared_ptr<Object::AI_Entity>> mSimEntities;
		std::vector<std::shared_ptr<Object::Base>>mSimEntities_Static;
		std::string mConfigLocation;
		std::shared_ptr<Assets::Registry> mAssetRegistry;
		std::shared_ptr<Render::Scene::Scene> mScene;

	private:
		void Environment::clearSimulationObjects();
		void clearScene();
	};
}