/*------------------------------------------------------------------------------
author: andywm, 2016
description:
3D camera defintion, provides basic camera
functionallity including panning, tilting, and space
traversal.
------------------------------------------------------------------------------*/

#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "scene_graph.h"
#include "so_includes.h"
#include "perspective_view.h"

namespace Environment
{
	namespace Object
	{
		/*
		camera class, provides 2 axis rotation and
		3D space navigation
		*/
		class Camera : public Base
		{
		public:
			enum class MODE { FREE, FOLLOW };
			//members//
		private:
			const float rotRate;
			const float linRate;
			const int linMultiplier;
			const int rotMultiplier;

			const MODE mMode;

			float mAspectRatio;

			//glm::mat4 mProjection; 
			glm::mat4 mRotation;
			glm::mat4 mTranslation;
			std::shared_ptr<Render::Scene::Graph::Xform> mSG_X;
			std::shared_ptr<Render::Scene::Graph::Camera> mSG_Cam;
			float pitch, yaw;
			int mObjectFocus;
			//methods//
		public:
			Camera(const glm::vec3 & pos, const glm::vec3 & orient, 
				const MODE mode, const int linr, const int rotr);
			Camera& operator=(const Camera&) = delete;
			~Camera() = default;
			void pan(const int by);
			void tilt(const int by);
			void move(const glm::vec3 & by);
			/*return the camera's projection matrix*/
			inline const glm::mat4
			Camera::projection() const
			{
				return Utilities::perspective(60.0f, mAspectRatio);
			}
		
			void aspectRatio(const float aspect);

			void deactivate();
			void activate();
			const int focus() const;
			void focus(const int f);
			
			virtual void simulate(const double deltaTime) override;
			virtual void buildSceneEntry(
				const std::shared_ptr<SG_Base> target) override;
		};
	}
}
#endif 