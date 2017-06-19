#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "scene_graph.h"
#include "so_camera.h"

namespace Render
{
	namespace Scene
	{
		class Scene
		{
		private:
			bool mSpecialRenderMode;
			bool mShowStatistics;
			glm::vec4 mBackground;
			std::unique_ptr<Graph::Linearise> mSGStatic;
			std::shared_ptr<Graph::Group> mSceneRoot;
			std::vector<std::shared_ptr<Environment::Object::Camera>> mCameras;
			int mActiveCamera;

		public:
			Scene();
			~Scene()=default;
			void submitToScene(const std::shared_ptr<Graph::SGBase> node);
			void generateStaticSG();
			void setAspect(const glm::vec2 & aspect);
			std::shared_ptr<Environment::Object::Camera> makeCamera(
				const glm::vec3 & pos, const glm::vec2 & orient, 
				Environment::Object::Camera::MODE, int lin, int rot);
			void activateCamera(const unsigned int index);
			void inject(const std::shared_ptr<Environment::Object::Base> obj);
			void destroySceneGraph();

			inline std::shared_ptr<Environment::Object::Camera> &
			Scene::camera()
			{
				return mCameras[mActiveCamera];
			}
			
			inline std::shared_ptr<Graph::SGBase>
			Scene::sceneRoot() const
			{
				return mSceneRoot;
			}

			inline std::vector <Graph::SGBase *>
			Scene::drawables() const
			{
				return mSGStatic->linearised();
			}

			inline Graph::Camera *
			Scene::sgCamera() const
			{
				return mSGStatic->viewInformation();
			}

			inline const bool
			specialRenderMode() const
			{
				return mSpecialRenderMode;
			}

			void
			specialRenderMode(const bool srm)
			{
				mSpecialRenderMode = srm;
			}

			inline const bool
			showStatistics() const
			{
				return mShowStatistics;
			}

			void
			showStatistics(const bool ss)
			{
				mShowStatistics = ss;
			}
		};
	}
}