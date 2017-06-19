#include <SDL2\SDL_events.h>
#include <exception>
#include <glm\glm.hpp>
#include "d3d_gpu_geometry.h"
#include "d3d_context.h"
#include <glm/gtx/transform.hpp>
#include <AntTweakBar.h> 
#include "so_camera.h"
#include "simulation.h"
#include "Scene.h"
#include "master.h"


//need to update aspect ratio when resized...

Simulation::Simulation(const std::string & assetDir)
	:
	mCardinals 
	{
		/*back   */ glm::vec3(+0.0f, +0.0f, -1.0f),
		/*forward*/ glm::vec3(+0.0f, +0.0f, +1.0f),
		/*left   */ glm::vec3(+1.0f, +0.0f, +0.0f),
		/*right  */ glm::vec3(-1.0f, +0.0f, +0.0f),
		/*up     */ glm::vec3(+0.0f, -1.0f, +0.0f),
		/*down   */ glm::vec3(+0.0f, +1.0f, +0.0f)
	},
	mRotation
	{
		/*up     */ +1,
		/*down   */ -1,
		/*left   */ +1,
		/*right  */ -1
	},
	mTerminate(false),
	mResetRequired(false),
	mWindow("08025/08975 ACW", 500, 500, 0),
	mUI_State{ INPUT_SCHEME::DEFAULT, false },
	mRegister(std::shared_ptr<Assets::Registry>(new Assets::Registry(assetDir)))
{
	//, mWorld(std::string(assetDir + "\\" + config), mRegister),

	mWorld = std::unique_ptr<Environment::Environment>
		(new Environment::Environment(mRegister));
}

bool
Simulation::runSimulation()
{
	const std::shared_ptr<Render::d3d11::D3DContext>
		context = mWindow.context();


	//configure world
	mWorld->generateWorld();
	Render::Pass::Master rp(context, mWorld->scene(), mRegister->shaderPaths());
	//initialise default states.
	mScene = mWorld->scene();
	mResetRequired = false;
	mTerminate = false;

	//resets the clock.
	mWorldClock.reset();

	//main program loop
	try
	{	
		Utilities::Clock frameRateCounter;
		int currentFrames = 0,  displayFrames=0;
		double seconds = 0.0;
		TwInit(TW_DIRECT3D11, context->device().Get());
		TwWindowSize(500, 500);
		TwBar * const bar = TwNewBar("Controls");
		const std::array<int,2> barSize = { 224, 320 };
		TwSetParam(bar, nullptr, "size", TW_PARAM_INT32, 2, &barSize);

		std::string f1 = "F1", f2 = "F2", f3 = "F3", f4 = "F4(broken)",
			f5="F5";
		std::string togStat = "S";
		std::string wasd = "W, A, S, D";
		std::string arrows = "Arrows";
		std::string arrowsMove = "Ctrl+Arrows";
		std::string mouse = "Mouse";
		std::string timeUp = "t", timeDown="T";
		std::string reload = "r";
		std::string quit = "ESC";
		TwAddVarRW(bar, "Camera 1", TW_TYPE_STDSTRING, &f1, "");
		TwAddVarRW(bar, "Camera 2", TW_TYPE_STDSTRING, &f2, "");
		TwAddVarRW(bar, "Camera 3", TW_TYPE_STDSTRING, &f3, "");
		TwAddVarRW(bar, "Toggle Focus", TW_TYPE_STDSTRING, &f4, "");
		TwAddVarRW(bar, "Toggle Render", TW_TYPE_STDSTRING, &f5, "");
		TwAddVarRW(bar, "Toggle Statistics", TW_TYPE_STDSTRING, &togStat, "");
		TwAddSeparator(bar, "sep", nullptr);
		TwAddVarRW(bar, "Rotate", TW_TYPE_STDSTRING, &arrows, "");
		TwAddVarRW(bar, "Move", TW_TYPE_STDSTRING, &arrowsMove, "");
		TwAddVarRW(bar, "Alt Rotate", TW_TYPE_STDSTRING, &mouse, "");
		TwAddVarRW(bar, "Alt Move", TW_TYPE_STDSTRING, &wasd, "");
		TwAddSeparator(bar, "sep2", nullptr);
		TwAddVarRW(bar, "Simspeed >", TW_TYPE_STDSTRING, &timeUp, "");
		TwAddVarRW(bar, "Simspeed <", TW_TYPE_STDSTRING, &timeDown, "");
		TwAddVarRW(bar, "Reload Config", TW_TYPE_STDSTRING, &reload, "");
		TwAddVarRW(bar, "Exit", TW_TYPE_STDSTRING, &quit, "");
		TwAddSeparator(bar, "sep3", nullptr);
		TwAddVarRW(bar, "FPS", TW_TYPE_INT32, &displayFrames, "");
		while (!mTerminate)
		{
			seconds += frameRateCounter.tick();
			if (seconds > 1)
			{
				displayFrames = currentFrames;
				currentFrames = 0;
				seconds = 0;
			}
			currentFrames++;
			userInputHandling();
			mWorld->advanceTime(mWorldClock.tick());

			rp.execute();			
			
		}
		TwTerminate();
		
	}
	catch (std::exception & e)
	{
		throw e;
	}
	return mResetRequired;
}

void 
Simulation::userInputHandling()
{
	mWM.propogateEvents();
	UI_Default();
	//control scheme is expandable, but since there aren't other
	//schemes currently, this is a pointless operation.
	/*
	switch (mUI_State.controlMode)
	{
	case INPUT_SCHEME::DEFAULT:
		{
			UI_Default();
			break;
		}
	}
	*/
}

void
Simulation::UI_Default()
{
	SDL_Event event;
	
	while (mWindow.popEvent(&event))
	{
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				mTerminate = true;
			}
			if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
				event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				mWindow.resized();
				TwWindowSize(mWindow.size().x, mWindow.size().y);
				mScene->setAspect(mWindow.size());
			}
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					mTerminate = true;
					break;
				case SDLK_r:
					mResetRequired = true;
					mTerminate = true;
					break;
				case SDLK_F1:
				{
					mScene->activateCamera(0);
					break;
				}
				case SDLK_F2:
				{
					mScene->activateCamera(1);
					break;
				}
				case SDLK_F3:
				{
					mScene->activateCamera(2);
					break;
				}
				case SDLK_F4:
				{
					mWorld->focusNext();
					break;
				}
				case SDLK_F5:
				{
					mScene->specialRenderMode(!mScene->specialRenderMode());
					break;
				}
				case SDLK_t:
				{
					const auto mod = event.key.keysym.mod;
					if (mod & SDLK_LSHIFT || mod & SDLK_RSHIFT)
					{
						mWorldClock.decreasePace();
					}
					else
					{
						mWorldClock.increasePace();
					}
					break;
				}

				//Camera Controls
				case SDLK_w:
				{
					mScene->camera()->move(mCardinals.FORWARD);
					break;
				}
				case SDLK_s:
				{
					const auto mod = event.key.keysym.mod;
					if (mod & SDLK_LCTRL || mod & SDLK_RCTRL)
						mScene->showStatistics(!mScene->showStatistics());
					else
						mScene->camera()->move(mCardinals.BACKWARD);
					break;
				}
				case SDLK_a:
				{
					mScene->camera()->move(mCardinals.LEFT);
					break;
				}
				case SDLK_d:
				{
					mScene->camera()->move(mCardinals.RIGHT);
					break;
				}
				case SDLK_q:
				{
					mScene->camera()->move(mCardinals.UP);
					break;
				}
				case SDLK_e:
				{
					mScene->camera()->move(mCardinals.DOWN);
					break;
				}

				//arrow key control.	
				case SDLK_UP:
				{
					const auto mod = event.key.keysym.mod;
					if (mod & SDLK_LCTRL || mod & SDLK_RCTRL)
					{
						mScene->camera()->move(mCardinals.UP);
					}
					else
					{
						mScene->camera()->tilt(mRotation.UP);
					}
					break;
				}
				case SDLK_LEFT:
				{
					const auto mod = event.key.keysym.mod;
					if (mod & SDLK_LCTRL || mod & SDLK_RCTRL)
					{
						mScene->camera()->move(mCardinals.LEFT);
					}
					else
					{
						mScene->camera()->pan(mRotation.LEFT);
					}
					break;
				}			
				case SDLK_DOWN:
				{
					const auto mod = event.key.keysym.mod;
					if (mod & SDLK_LCTRL || mod & SDLK_RCTRL)
					{
						mScene->camera()->move(mCardinals.DOWN);
					}
					else
					{
						mScene->camera()->tilt(mRotation.DOWN);
					}
					break;
				}
				case SDLK_RIGHT:
				{
					const auto mod = event.key.keysym.mod;
					
					if (mod & SDLK_LCTRL || mod & SDLK_RCTRL)
					{
						mScene->camera()->move(mCardinals.RIGHT);
					}
					else
					{
						mScene->camera()->pan(mRotation.RIGHT);
					}
					break;
				}
				case SDLK_PAGEUP:
				{
					mScene->camera()->move(mCardinals.UP);
					break;
				}
				case SDLK_PAGEDOWN:
				{
					mScene->camera()->move(mCardinals.DOWN);
					break;
				}
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mUI_State.mouseDown = true;
		if (event.type == SDL_MOUSEBUTTONUP)
			mUI_State.mouseDown = false;
		if (event.type == SDL_MOUSEMOTION && mUI_State.mouseDown)
		{
			mScene->camera()->pan(event.motion.xrel);
			mScene->camera()->tilt(event.motion.yrel);
		}

		//F4 switches to follow object
		//F5 switches render modes...
	}
}