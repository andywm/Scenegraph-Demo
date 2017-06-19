#include <memory>
#include <glm\glm.hpp>
#include "Scene.h"

namespace Render
{
	namespace Scene
	{
		Scene::Scene()
			:
			mBackground(glm::vec4(0.5f,0.5f,0.5f, 1.0f)),
			mSceneRoot(new Graph::Group),
			mActiveCamera(0),
			mSpecialRenderMode(false),
			mShowStatistics(true)
		{}

		std::shared_ptr<Environment::Object::Camera>
		Scene::makeCamera(const glm::vec3 & pos, const glm::vec2 & orient, 
			Environment::Object::Camera::MODE mode, int lin, int rot)
		{
			mCameras.push_back(
				std::unique_ptr<Environment::Object::Camera>(
						new Environment::Object::Camera(
							pos, glm::vec3(orient, 0.0f), mode, lin, rot)));
			return mCameras[mCameras.size() - 1];
		}

		void
		Scene::activateCamera(const unsigned int index)
		{
			if (index < mCameras.size())
			{
				for (const auto & cam : mCameras)
				{
					cam->deactivate();
				}
				mActiveCamera = index;
				mCameras[mActiveCamera]->activate();
			}
		}

		void 
		Scene::submitToScene(const std::shared_ptr<Graph::SGBase> node)
		{
			mSceneRoot->add(node, mSceneRoot);
		}
	
		void
		Scene::generateStaticSG()
		{
			mSGStatic = std::unique_ptr<Graph::Linearise>
				(new Graph::Linearise(mSceneRoot));
		}

	
		void 
		Scene::setAspect(const glm::vec2 & aspect)
		{
			if (!mCameras.empty())
			{
				for (const auto & c : mCameras)
				{
					c->aspectRatio(static_cast<float>(aspect.x) / 
						static_cast<float>(aspect.y));
				}
			}
		}

		/*
			warning, orphans all elements in the scenegraph, all external
			references to those objects must also be freed for the memory to 
			be released.
		*/
		void 
		Scene::destroySceneGraph()
		{
			const Graph::Orphanise orphan;
			mSceneRoot->accept(&orphan);
			mSGStatic = nullptr;
		}

		void 
		Scene::inject(const std::shared_ptr<Environment::Object::Base> obj)
		{
			const auto element = mCameras[mActiveCamera]->sgRepresentation();
			obj->injectIntoCS(element);
		}
	}
}