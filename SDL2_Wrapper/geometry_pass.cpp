#include <memory>
#include <vector>
#include "geometry_stage.h"
#include "render_state.h"
#include "scene_graph.h"

namespace Render
{
	namespace Stage
	{
		Geometry::Geometry(std::shared_ptr<Render::State> & d)
			:
			Base(d)
		{}

		void 
		Geometry::execute()
		{
			//mSceneState->scene->sceneRoot();
			auto leaves = sceneState()->scene()->drawables();
			const auto camera = sceneState()->scene()->sgCamera();

			Render::Scene::Graph::WorldTransform wt;
			wt.visit(camera);
			sceneState()->context()->pipeline().projection(camera->projection());
			sceneState()->context()->pipeline().view(wt.transform());
		

			sceneState()->context()->execute(ACTION::COMMIT_VP);
			sceneState()->context()->execute(ACTION::COMMIT_SHADER);

			for (auto & leaf : leaves)
			{
				//auto s = mSceneState->context()->pipeline().state();
				if (leaf->isA(Scene::Graph::IDENTITY::GEOMETRY))
				{
					//get the geometry.
					auto & geo = (reinterpret_cast<Scene::Graph::Geometry*&>
						(leaf));
					//calculate its transform wrt the world origin
					wt.visit(geo);
					sceneState()->context()->pipeline().model(wt.transform());
					//set the geometry and instruct the context to draw it.
					sceneState()->context()->pipeline().geometry(geo->mesh());
					sceneState()->context()->pipeline().material(
							geo->material());
					sceneState()->context()->pipeline().texture(
						geo->texture());
					sceneState()->context()->execute(ACTION::GEOMETRY);
				}
			}	
		}
	}
}